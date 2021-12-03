/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:11 by dalves-p          #+#    #+#             */
/*   Updated: 2021/12/03 13:20:16 by dalves-p         ###   ########.fr       */
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

	printf("%s\n", pipex->infile);
	printf("%s\n", pipex->outfile);
	
	pipex->cmds = malloc((argc - 3) * sizeof(char *));
	i = 2;
	while (i < pipex->argc - 1)
	{
		pipex->cmds[i - 2] = argv[i];
		printf("%s\n", pipex->cmds[i - 2]);
		i++;
	}
	while (*envp)
	{
		if (ft_strstr(*envp, "PATH") != 0)
			pipex->path = *envp;
		envp++;
	}
	printf("%s\n", pipex->path);
	return (0);
}


int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	init(&pipex, argc, argv, envp);
	free(pipex.cmds);
	return (0);
}
