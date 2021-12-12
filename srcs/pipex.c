/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:11 by dalves-p          #+#    #+#             */
/*   Updated: 2021/12/12 20:44:19 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**get_cmd(char *cmds)
{
	char	**cmd;
	int		i;

	printf("\ncmds: %s\n", cmds);
	cmd = ft_split_pipex(cmds, ' ');
	i = 0;
	while (cmd[i])
	{
		if (ft_strstr(cmd[i], "'") != 0 )
		{
			cmd[i] = ft_strtrim(cmd[i], "'");	
		}
		i++;
	}
	return (cmd);
}

char	*get_path(char *envp[], char *cmd)
{
	char	*path;
	char	*full_path;
	char	**ptr_paths;
	char	*selected_path;
	int		i;

	while (*envp)
	{
		if (ft_strstr(*envp, "PATH") != 0)
			path = *envp;
		envp++;
	}
	full_path = ft_strtrim(path, "PATH=");
	ptr_paths = ft_split(full_path, ':');
	i = 0;
	while (ptr_paths[i])
	{
		selected_path = ft_strjoin(ft_strjoin(ptr_paths[i], SEPARATOR), cmd);
		if (access(selected_path, F_OK) == 0)
			return (selected_path);
		i++;
	}
	return ("error");
}

int	child_process(char *argv[], char *envp[], int fd[2])
{
	int		infile_fd;
	char	**cmd;
	char	*path;
	int		err;

	close(fd[FD_R]);
	infile_fd = open(argv[1], O_RDONLY, 0777);
	if (infile_fd == -1)
		error("\e[31m\e[1mError while opening infile\e[0m\n");
	dup2(fd[FD_W], STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	close(fd[FD_W]);
	cmd = get_cmd(argv[2]);
	path = get_path(envp, cmd[0]);
	err = execve(path, cmd, envp);
	if (err == -1)
		error("\e[31m\e[1mCould not find program to execute!\e[0m\n");
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
		error("\e[31m\e[1mError while opening outfile\e[0m\n");
	dup2(fd[FD_R], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(fd[FD_W]);
	close(fd[FD_R]);
	cmd = get_cmd(argv[3]);
	path = get_path(envp, cmd[0]);
	err = execve(path, cmd, envp);
	if (err == -1)
	{
		unlink(argv[argc - 1]);		
		error("\e[31m\e[1mCould not find program to execute!\e[0m\n");
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	int		pid;
	int		wstatus;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error("\e[31m\e[1mError while opening the pipe\e[0m\n");
		pid = fork();
		if (pid == -1)
			error("\e[31m\e[1mError while forking\e[0m\n");
		if (pid == 0)
			child_process(argv, envp, fd);
		else
		{
			wait(&wstatus);
			if (WEXITSTATUS(wstatus) == 0)
				parent_process(argc, argv, envp, fd);
		}		
		return (0);
	}
	else
		error("\e[31m\e[1mError: check your arguments\n\
Ex: ./pipex <infile> <cmd1> <cmd2> <outfile>\e[0m\n");
}
