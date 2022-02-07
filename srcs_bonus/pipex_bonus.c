/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:11 by dalves-p          #+#    #+#             */
/*   Updated: 2022/02/08 00:07:02 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	first_process(t_pipex pipex, int pipe_fd[][2], int i)
{
	int		infile_fd;
	char	*buffer;

	if (pipex.here_doc == 1)
	{
		write(1, "here_doc> ", 10);
		buffer = get_next_line(STDIN_FILENO);
	}
	else
	{
		infile_fd = open(pipex.infile, O_RDONLY, 0777);
		if (infile_fd == -1)
			error("No such file or directory", EXIT_FAILURE);
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);		
	}
	dup2(pipe_fd[i + 1][FD_W], STDOUT_FILENO);
	close(pipe_fd[i][FD_W]);
	return (0);
}

int	child_process(char *envp[], t_pipex pipex, int pipe_fd[][2], int i)
{
	char	**cmd;
	char	*path;
	int		j;

	j = -1;
	// vou usar pipe de leitura de i e pipe de escrita de i + 1
	// então: fechar todos os pipes de leitura diferente de i
	// e todos os pipes de escrita diferente de i + 1
	while (++j < pipex.count_cmds + 1)
	{
		// fecho todos de leitura, menos o i = j
		if (i != j)
			close(pipe_fd[j][FD_R]);
		// fecho todos de escrite, menos o i + 1 = j
		if (i + 1 != j)
			close(pipe_fd[j][FD_W]);
	}

	// primeiro processo:
		// lê do infile
		// escreve no pipe[0]
	if (i == 0)
	{
		// printf("Proceso: %d\n", i);
		// printf("Comando: %s\n", pipex.cmds[i]);
		first_process(pipex, pipe_fd, i);	
	}
	// processos do meio  (n):
		// lê do pipe[n]
		// escreve no pipe[n+1]
	else if (i > 0 && i < pipex.count_cmds - 1 && pipex.count_cmds > 2)
	{
		// printf("Proceso: %d\n", i);
		// printf("Comando: %s\n", pipex.cmds[i]);
		dup2(pipe_fd[i][FD_R], STDIN_FILENO);
		dup2(pipe_fd[i + 1][FD_W], STDOUT_FILENO);	
		close(pipe_fd[i][FD_R]);
		close(pipe_fd[i + 1][FD_W]);
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

int	last_process(char *envp[], t_pipex pipex, int pipe_fd[][2])
{
	int		outfile_fd;
	char	**cmd;
	char	*path;
	int		j;

	// printf("Último Proceso: %d\n", pipex.count_cmds - 1);
	// printf("Último Comando: %s\n", pipex.cmds[pipex.count_cmds - 1]);
	j = 0;
	while (j < pipex.count_cmds)
	{
		if (pipex.count_cmds - 1 != j)
			close(pipe_fd[j][FD_R]);
		if (pipex.count_cmds != j)
			close(pipe_fd[j][FD_W]);
		j++;
	}
	if (pipex.here_doc == 0)
		outfile_fd = open(pipex.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		outfile_fd = open(pipex.outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (outfile_fd == -1)
		error("No such file or directory", EXIT_FAILURE);
	dup2(pipe_fd[pipex.count_cmds - 1][FD_R], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(pipe_fd[pipex.count_cmds - 1][FD_R]);
	close(outfile_fd);
	cmd = get_cmd(pipex.cmds[pipex.count_cmds - 1]);
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
	printf("Número de processos: %d\n", pipex.count_cmds);
	// Criar n - 1 processos
	i = -1;
	while (++i < pipex.count_cmds - 1)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			error("Error while calling fork", EXIT_FAILURE);
		if (pid[i] == 0)
			child_process(envp, pipex, pipe_fd, i);
	}
	// último processo
	if (++i == pipex.count_cmds)
	{
		//Main process ????????
		waitpid(-1, NULL, WNOHANG);
		last_process(envp, pipex, pipe_fd);		
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if ((ft_strcmp(argv[1], "here_doc")) == 0)
		init_here_doc(argc, argv, envp, &pipex);
	else
		init(argc, argv, envp, &pipex);
	if ((argc >= 5 && pipex.here_doc == 0) || (argc >= 6 && pipex.here_doc == 1))
		run_pipex(pipex, envp);
	else if (argc == 3)
	{
		open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		error("Error: check your arguments\n\
usage: ./pipex <infile> <cmd1> ... <cmd2> <outfile>", 0);
	}
	else
		error("Error: check your arguments\n\
usage: ./pipex <infile> <cmd1> <cmd2> ... <cmdn> <outfile>\n\
or\n\
./pipex here_doc LIMITER <cmd2> ... <cmdn> <outfile>", EXIT_FAILURE);
}
