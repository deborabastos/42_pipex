/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:11 by dalves-p          #+#    #+#             */
/*   Updated: 2021/12/08 12:02:38 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	init(t_pipex *pipex, int argc, char *argv[])
{
	int		i;

	pipex->argc = argc;
	pipex->infile = argv[1];
	pipex->outfile = argv[pipex->argc - 1];
	pipex->cmds = malloc((argc - 3) * sizeof(char *));
	i = 2;
	while (i < pipex->argc - 1)
	{
		pipex->cmds[i - 2] = argv[i];
		i++;
	}
	return (0);
}

char	**get_cmd(char *cmds)
{
	char	**cmd;

	cmd = ft_split(cmds, ' ');
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

int	child_process(t_pipex *pipex, char *envp[], int fd[2])
{
	int		infile_fd;
	char	**cmd;
	char	*path;
	int		err;

	close(fd[FD_R]);
	infile_fd = open(pipex->infile, O_RDONLY, 0777);
	if (infile_fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd[FD_W], STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	close(fd[FD_W]);
	cmd = get_cmd(pipex->cmds[0]);
	path = get_path(envp, cmd[0]);
	err = execve(path, cmd, envp);
	if (err == -1)
	{
		ft_putstr_fd("\033[31mCould not find program to execute!\e[0m\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	parent_process(t_pipex *pipex, char *envp[], int fd[2])
{
	int		outfile_fd;
	char	**cmd;
	char	*path;
	int		err;

	close(fd[FD_W]);
	outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd[FD_R], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(fd[FD_W]);
	close(fd[FD_R]);
	cmd = get_cmd(pipex->cmds[1]);
	path = get_path(envp, cmd[0]);
	err = execve(path, cmd, envp);
	if (err == -1)
	{
		ft_putstr_fd("\033[31mCould not find program to execute!\e[0m\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		fd[2];
	int		pid;
	int		wstatus;
	int		status_code;

	if (argc == 5 )
	{
		init(&pipex, argc, argv);
		if (pipe(fd) == -1)
		{
			ft_putstr_fd("\033[A error ocurred while opening the pipe\n\e[0m", 2);
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
			child_process(&pipex, envp, fd);
		else
		{
			wait(&wstatus);
			if (WEXITSTATUS(wstatus) == 0)
			{
				status_code = WEXITSTATUS(wstatus);
				if (status_code == 0)
					parent_process(&pipex, envp, fd);
				else
					exit(EXIT_FAILURE);
			}
		}		
		free(pipex.cmds);
		return (0);
	}
	else
	{
		ft_putstr_fd("\033[31mError: check your arguments\n \
Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n\e[0m", 2);
		exit(EXIT_FAILURE);
	}
}
