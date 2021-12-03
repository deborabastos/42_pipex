/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:11 by dalves-p          #+#    #+#             */
/*   Updated: 2021/12/03 11:58:00 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// < pipex.h cat | wc -l
// receber os parametros e separa-los em file e comando
// executar o primeiro comando no primeiro arquivo
// mandar resultado da primeira execução para o segundo comando (via pipe)
// executar segundo comando
// gravar output no segundo arquivo

// int	test_path(char cmd, char *envp[])
// {
	// while (*envp)
	// {
	// 	// Pegar apenas PATH
	// 	// Separar por :
	// 	// Testar cada path com o comando
	// 	// usar access()
	// 	// printf("%s\n", *envp);
	// 	envp++;
	// }	
	// return (0);
// }

// int	parsing(t_pipex	pipex, char *argv[], char *envp[])
// {
	// while (*argv)
	// {
	// 	// separar files de cmds
	// 	// primeiro e último são files
	// 	printf("%s\n", argv[0]);
	// 	argv++;
	// }
	// return (0);
// }

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	t_pipex	pipex;

	pipex.argc = argc;
	pipex.infile = argv[1];
	pipex.outfile = argv[pipex.argc - 1];

	printf("%s\n", pipex.infile);
	printf("%s\n", pipex.outfile);

	printf("%i\n", argc);
	printf("%i\n", pipex.argc - 1);

	pipex.cmds = malloc((argc - 3) * sizeof(char *));
	i = 2;
	while (i < pipex.argc - 1)
	{
		pipex.cmds[i - 2] = argv[i];
		printf("%s\n", pipex.cmds[i - 2]);
		i++;
	}




	free(pipex.cmds);
	return (0);
}
