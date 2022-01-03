/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:11 by dalves-p          #+#    #+#             */
/*   Updated: 2021/12/27 11:05:17 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	child_process(char *envp[], t_pipex pipex, int fd[2])
{
	int		i;
	int		infile_fd;
	char	**cmd;
	char	*path;
	
	i = -1;
	while (++i < pipex.count_cmds + 1)
	{
		close(fd[i][FD_R]);
	}
	infile_fd = open(pipex.infile, O_RDONLY, 0777);
	if (infile_fd == -1)
		error("No such file or directory", EXIT_FAILURE);
	dup2(fd[FD_W], STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	close(fd[FD_W]);
	cmd = get_cmd(pipex.cmds[0]);
	path = get_path(pipex.paths, cmd[0]);
	if (execve(path, cmd, envp) == -1)
		error("command not found", 127);
	return (0);
}

int	parent_process(char *envp[], t_pipex pipex, int fd[2])
{
	int		outfile_fd;
	char	**cmd;
	char	*path;
	int		err;

	close(fd[FD_W]);
	outfile_fd = open(pipex.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
		error("No such file or directory", EXIT_FAILURE);
	dup2(fd[FD_R], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(fd[FD_W]);
	close(fd[FD_R]);
	cmd = get_cmd(pipex.cmds[1]);
	path = get_path(pipex.paths, cmd[0]);
	err = execve(path, cmd, envp);
	if (err == -1)
		error("command not found", 127);
	return (0);
}

t_pipex	init(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		i;
	char	*env_paths;
	char	*full_path;

	pipex.argc = argc;
	pipex.count_cmds = argc - 3;
	pipex.infile = argv[1];
	pipex.outfile = argv[argc - 1];
	pipex.cmds = malloc(pipex.count_cmds * sizeof(char *));
	i = 0;
	while (i < pipex.count_cmds)
	{
		pipex.cmds[i] = malloc(ft_strlen(argv[i + 2]) * sizeof(char));
		pipex.cmds[i] = argv[i + 2];
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
	pipex.paths = ft_split_pipex(full_path, ':');
	free(full_path);
	return (pipex);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		pipe_fd[argc + 1][2];
	int		pid[argc];
	int		i;

	pipex = init(argc, argv, envp);
	if (argc >= 5)
	{
		i = -1;
		while (++i < pipex.count_cmds + 1)
		{
			if (pipe(pipe_fd[i]) == -1)
				error("Error while calling pipe", EXIT_FAILURE);
		}
		i = -1;
		while (++i < pipex.count_cmds)
		{
			pid[i] = fork();
			if (pid[i] == -1)
				error("Error while calling fork", EXIT_FAILURE);
			if (pid[i] == 0)
				child_process(envp, pipex, pipe_fd[i]);
			else
				parent_process(envp, pipex, pipe_fd[i]);
		}
	}
	else
		error("Error: check your arguments\n\
usage: ./pipex <infile> <cmd1> <cmd2> ... <cmdn> <outfile>", EXIT_FAILURE);
}
