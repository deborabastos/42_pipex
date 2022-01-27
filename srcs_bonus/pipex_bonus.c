/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:11 by dalves-p          #+#    #+#             */
/*   Updated: 2022/01/27 19:25:47 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	child_process(char *envp[], t_pipex pipex, int pipe_fd[][2], int i)
{
	int		infile_fd;
	int		outfile_fd;
	char	**cmd;
	char	*path;
	int		j;

	// printf("Proceso: %d\n", i);
	// printf("Comando: %s\n", pipex.cmds[i]);
	j = 0;
	// vou usar pipe de leitura de i, de escrita de i + 1
	// fechar todos os pipes de leitura diferente de i
	// e todos os pipes de escrita diferente de i +1
	while (j < pipex.count_cmds + 1)
	{
		// fecho todos de leitura, menos o i = j
		if (i != j)
			close(pipe_fd[j][FD_R]);
		// fecho todos de escrite, menos o i + 1 = j
		if (i + 1 != j)
			close(pipe_fd[j][FD_W]);
		j++;
	}

	// primeiro processo:
		// lê do infile
		// escreve no pipe[0]
	if (i == 0)
	{
		infile_fd = open(pipex.infile, O_RDONLY, 0777);
		if (infile_fd == -1)
			error("No such file or directory", EXIT_FAILURE);
		dup2(infile_fd, STDIN_FILENO);
		dup2(pipe_fd[i + 1][FD_W], STDOUT_FILENO);
		close(infile_fd);
		close(pipe_fd[i][FD_W]);		
	}
	// processos do meio  (n):
		// lê do pipe[n]
		// escreve no pipe[n+1]
	else if (i > 0 && i < pipex.count_cmds - 1)
	{
		dup2(pipe_fd[i][FD_R], STDIN_FILENO);
		dup2(pipe_fd[i + 1][FD_W], STDOUT_FILENO);
		close(pipe_fd[i][FD_R]);
		close(pipe_fd[i + 1][FD_W]);			
	}
	// último processo:
		// lê do pipe[n]
		// escreve no outfile
	else if (i == pipex.count_cmds - 1)
	{
		outfile_fd = open(pipex.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (outfile_fd == -1)
			error("No such file or directory", EXIT_FAILURE);
		dup2(pipe_fd[i][FD_R], STDIN_FILENO);
		dup2(outfile_fd, STDOUT_FILENO);
		close(pipe_fd[i][FD_R]);
		close(outfile_fd);
	}
	cmd = get_cmd(pipex.cmds[i]);
	path = get_path(pipex.paths, cmd[0]);
	if (execve(path, cmd, envp) == -1)
	{
		if (path != cmd[0])
			free(path);
		ft_free_ptrptr(cmd);
		error("command not found", 127);
	}
	return (0);
}

void	init(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	int		i;
	char	*env_paths;
	char	*full_path;

	pipex->argc = argc;
	pipex->count_cmds = argc - 3;
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->cmds = malloc(pipex->count_cmds * sizeof(char *));
	i = 0;
	while (i < pipex->count_cmds)
	{
		pipex->cmds[i] = malloc(ft_strlen(argv[i + 2]) * sizeof(char));
		pipex->cmds[i] = argv[i + 2];
		i++;
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strstr(envp[i], "PATH") != 0)
			env_paths = envp[i];
		i++;
	}
	full_path = ft_strtrim(env_paths, "PATH=");
	pipex->paths = ft_split_pipex(full_path, ':');
	free(full_path);
}


int run_pipex(t_pipex pipex, char *envp[])
{
	// precisamos de n (argc - 3) processos = pipex.count_cmds
	// precisamos de n + 1 (argc - 2) pipes		

	int		pipe_fd[pipex.count_cmds + 1][2];
	int		pid[pipex.count_cmds];
	int		i;

	// Abrir n + 1 pipes
	i = -1;
	while (++i < pipex.count_cmds + 1)
	{
		if (pipe(pipe_fd[i]) == -1)
			error("Error while calling pipe", EXIT_FAILURE);
	}
	//printf("Número de processos: %d\n", pipex.count_cmds);
	// Criar n processos
	i = -1;
	while (++i < pipex.count_cmds)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			error("Error while calling fork", EXIT_FAILURE);
		if (pid[i] == 0)
			child_process(envp, pipex, pipe_fd, i);
	}
	//Main process ????????
	waitpid(-1, NULL, WNOHANG);
	return (0);
}



int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	init(argc, argv, envp, &pipex);
	if (argc >= 5)
		run_pipex(pipex, envp);
	else if (argc == 3)
	{
		open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		error("Error: check your arguments\n\
usage: ./pipex <infile> <cmd1> <cmd2> <outfile>", 0);
	}
	else
		error("Error: check your arguments\n\
usage: ./pipex <infile> <cmd1> <cmd2> ... <cmdn> <outfile>", EXIT_FAILURE);
}
