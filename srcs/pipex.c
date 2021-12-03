/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:11 by dalves-p          #+#    #+#             */
/*   Updated: 2021/12/03 18:57:07 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// < pipex.h cat | wc -l
// receber os parametros e separa-los em file e comando
// executar o primeiro comando no primeiro arquivo
// mandar resultado da primeira execução para o segundo comando (via pipe)
// executar segundo comando
// gravar output no segundo arquivo

int init(t_pipex *pipex, int argc, char *argv[], char *envp[])
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
	while (*envp)
	{
		if (ft_strstr(*envp, "PATH") != 0)
			pipex->path = *envp;
		envp++;
	}
	// printf("%s\n", pipex->path);
	return (0);
}

int child_process(t_pipex *pipex, int fd[2])
{
	int		infile_fd;

	printf("AQUIII %s\n", pipex->cmds[0]);
	infile_fd = open(pipex->infile, O_RDONLY, 0777);
	dup2(fd[1], 1); // STDOUT_FILENO => escrever o resultado no pipe
	dup2(infile_fd, 0); // STDIN_FILENO => colocar a leitura do infile no stdin
	close(fd[0]);
	
	execve("/bin/ls", "ls -l", &pipex->path);
	
	return (0);
}


int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int 	fd[2];
	int		pid;

	init(&pipex, argc, argv, envp);

	if (pipe(fd) == -1)
	{
		printf("A error ocurred while opening the pipe\n");
		return 1;
	}
	pid = fork();
	if (pid == 0)
	{
		printf("Child\n");
		child_process(&pipex, fd);		
	}
	else
	{
		// Parent process - read from pipe
		wait(NULL);
		printf("Parent\n");
		
		// close(fd[1]); // fecha write
		// lê resultado do pipe

		// executa função

		// close(fd[0]); // fecha read
	}

	
	free(pipex.cmds);
	return (0);
}
