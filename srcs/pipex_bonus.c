/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:11 by dalves-p          #+#    #+#             */
/*   Updated: 2021/12/16 19:19:24 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	**get_cmd(char *cmds)
{
	char	**cmd;
	int		i;

	cmd = ft_split_pipex(cmds, ' ');
	i = 0;
	while (cmd[i])
	{
		if (ft_strstr(cmd[i], "'") != 0)
		{
			cmd[i] = ft_strtrim(cmd[i], "'");
		}
		i++;
	}
	return (cmd);
}

char	*get_path(char *envp[], char *cmd)
{
	char	**ptr_paths;
	char	*ptr_path;
	char	*selected_path;
	int		i;

	ptr_paths = get_full_path(envp);
	i = 0;
	while (ptr_paths[i])
	{
		ptr_path = ft_strjoin(ptr_paths[i], SEPARATOR);
		selected_path = ft_strjoin(ptr_path, cmd);
		if (access(selected_path, F_OK) == 0)
			return (selected_path);
		free(ptr_path);
		free(ptr_paths[i]);
		free(selected_path);
		i++;
	}
	free(ptr_paths);
	return (cmd);
}

int	child_process(char *argv[], char *envp[], int fd[2])
{
	int		infile_fd;
	char	**cmd;
	char	*path;

	close(fd[FD_R]);
	infile_fd = open(argv[1], O_RDONLY, 0777);
	if (infile_fd == -1)
		error("No such file or directory", EXIT_FAILURE);
	dup2(fd[FD_W], STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	close(fd[FD_W]);
	cmd = get_cmd(argv[2]);
	path = get_path(envp, cmd[0]);
	if (execve(path, cmd, envp) == -1)
		error("command not found", 127);
	return (0);
}

int	parent_process(int argc, char *argv[], char *envp[], int fd[2])
{
	int		outfile_fd;
	char	**cmd;
	char	*path;
	int		err;

	close(fd[FD_W]);
	outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
		error("No such file or directory", EXIT_FAILURE);
	dup2(fd[FD_R], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(fd[FD_W]);
	close(fd[FD_R]);
	cmd = get_cmd(argv[3]);
	path = get_path(envp, cmd[0]);
	err = execve(path, cmd, envp);
	if (err == -1)
		error("command not found", 127);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	int		pid;

	if (argc >= 5)
	{
		if (pipe(fd) == -1)
			error("Error while calling pipe", EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			error("Error while calling fork", EXIT_FAILURE);
		if (pid == 0)
			child_process(argv, envp, fd);
		else
			parent_process(argc, argv, envp, fd);
	}
	else
		error("Error: check your arguments\n\
usage: ./pipex <infile> <cmd1> <cmd2> ... <cmdn> <outfile>", EXIT_FAILURE);
}
