/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:11 by dalves-p          #+#    #+#             */
/*   Updated: 2021/12/02 22:23:06 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// < pipex.h cat | wc -l
// receber os parametros e separa-los em file e comando
// executar o primeiro comando no primeiro arquivo
// mandar resultado da primeira execução para o segundo comando (via pipe)
// executar segundo comando
// gravar output no segundo arquivo

int	parsing(char *argv[], char *envp[])
{
	while (*argv)
	{
		printf("%s\n", argv[0]);
		argv++;
	}
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	parsing(argv, envp);
	return (0);
}
