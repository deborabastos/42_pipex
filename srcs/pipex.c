/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:11 by dalves-p          #+#    #+#             */
/*   Updated: 2021/12/08 11:23:44 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// < pipex.h cat | wc -l
// receber os parametros e separa-los em file e comando
// executar o primeiro comando no primeiro arquivo
// mandar resultado da primeira execução para o segundo comando (via pipe)
// executar segundo comando
// gravar output no segundo arquivo

int init(t_pipex *pipex, int argc, char *argv[])
{
	int		i;

	pipex->argc = argc;
	pipex->infile = argv[1];
	pipex->outfile = argv[pipex->argc - 1];

	// printf("%s\n", pipex->infile);
	// printf("%s\n", pipex->outfile);
	
	pipex->cmds = malloc((argc - 3) * sizeof(char *));
	i = 2;
	while (i < pipex->argc - 1)
	{
		pipex->cmds[i - 2] = argv[i];
		// printf("%s\n", pipex->cmds[i - 2]);
		i++;
	}
	return (0);
}

char	**get_cmd(char *cmds)
{
	char	**cmd;
	
	// printf("COMANDOS: %s\n", cmds);
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
	// printf("Trimmed: %s\n", full_path);
	ptr_paths = ft_split(full_path, ':');
	// printf("Path: %s\n", ptr_paths[6]);
	i = 0;
	while (ptr_paths[i])
	{
		selected_path = ft_strjoin(ft_strjoin(ptr_paths[i], SEPARATOR), cmd);
		// printf("Selected path %s\n", selected_path);
		if (access(selected_path, F_OK) == 0)
		{
			// printf("Correct path %s\n", selected_path);
			return (selected_path);
		}
		i++;
	}
	return ("error");
}

int child_process(t_pipex *pipex, char *envp[], int fd[2])
{
	int		infile_fd;
	char	**cmd;
	char	*path;
	int		err;

	// printf("Primeiro comando %s\n", pipex->cmds[0]);
	close(fd[FD_R]); // fecho o read do pipe
	infile_fd = open(pipex->infile, O_RDONLY, 0777);
	if (infile_fd == -1)
		exit(EXIT_FAILURE);	
	dup2(fd[FD_W], STDOUT_FILENO); // STDOUT_FILENO = 1=> altera o stdout para o pipe (escrever o resultado no pipe)
	dup2(infile_fd, STDIN_FILENO); // STDIN_FILENO = 0 => colocar a leitura do infile no stdin
	close(infile_fd);
	close(fd[FD_W]); // fecho o read do pipe
	cmd = get_cmd(pipex->cmds[0]);
	path = get_path(envp, cmd[0]);
	err = execve(path, cmd, envp);	
	if (err == -1)
	{
		ft_putstr_fd("\033[31mCould not find program to execute - child!\e[0m\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}


int parent_process(t_pipex *pipex, char *envp[], int fd[2])
{
	int		outfile_fd;
	char	**cmd;
	char	*path;
	int		err;

	close(fd[FD_W]); // fecho o write do pipe
	// lê resultado do pipe
	outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd[FD_R], STDIN_FILENO); // STDIN_FILENO = 0 => lê o que vem do pipe (pipe se torna sdtin)
	dup2(outfile_fd, STDOUT_FILENO); // STDOUT_FILENO = 1 => colocar a escrita do outfile no stdout
	close(outfile_fd);
	close(fd[FD_W]); // fecho o read do pipe
	close(fd[FD_R]); // fecha read		

	// printf("%s\n", pipex->cmds[1]);
	cmd = get_cmd(pipex->cmds[1]);

	// printf("%s\n", cmd[0]);
	// printf("%s\n", cmd[1]);
	// printf("%s\n", cmd[2]);

	path = get_path(envp, cmd[0]);
	// printf("%s\n", path);
	err = execve(path, cmd, envp);
	if (err == -1)
	{
		ft_putstr_fd("\033[31mCould not find program to execute - parent!\e[0m\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int 	fd[2];
	int		pid;
	int		wstatus;

	if (argc == 5 )
	{
		init(&pipex, argc, argv);

		if (pipe(fd) == -1)
		{
			printf("A error ocurred while opening the pipe\n");
			return 1;
		}
		pid = fork();
		if (pid == -1)
		{
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			child_process(&pipex, envp, fd);	
		}
		else
		{
			wait(&wstatus);
			if (wstatus != 256)
			{
				parent_process(&pipex, envp, fd);
			}
			else
			{
				exit(EXIT_FAILURE);
			}
		}

		
		free(pipex.cmds);
		return (0);		
	}
	else 
	{
		ft_putstr_fd("\033[31mError: check your arguments\nEx: ./pipex <file1> <cmd1> <cmd2> <file2>\n\e[0m", 2);
		exit(EXIT_FAILURE);
	}

}
