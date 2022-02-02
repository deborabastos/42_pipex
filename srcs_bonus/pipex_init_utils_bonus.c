/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:06:24 by coder             #+#    #+#             */
/*   Updated: 2022/01/29 23:14:59 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	init_path(char *envp[], t_pipex *pipex)
{
	int		i;
	char	*env_paths;
	char	*full_path;

	i = 0;
	while (envp[i])
	{
		if (ft_strstr(envp[i], "PATH") != 0)
			env_paths = envp[i];
		i++;
	}
	full_path = ft_strtrim(env_paths, "PATH=");
	pipex->paths = ft_split_pipex(full_path, ':');
	free(full_path);	
}

void	init(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	int		i;

	pipex->argc = argc;
	pipex->count_cmds = argc - 3;
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->here_doc = 0;
	pipex->limiter = 0;
	pipex->cmds = malloc(pipex->count_cmds * sizeof(char *));
	i = 0;
	while (i < pipex->count_cmds)
	{
		pipex->cmds[i] = malloc(ft_strlen(argv[i + 2]) * sizeof(char));
		pipex->cmds[i] = argv[i + 2];
		i++;
	}
	init_path(envp, &pipex);
}

void	init_here_doc(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	int		i;
	char	*env_paths;
	char	*full_path;

	pipex->argc = argc;
	pipex->count_cmds = argc - 4;
	pipex->infile = 0;
	pipex->outfile = argv[argc - 1];
	pipex->here_doc = 1;
	pipex->limiter = argv[1];
	pipex->cmds = malloc(pipex->count_cmds * sizeof(char *));
	i = 0;
	while (i < pipex->count_cmds)
	{
		pipex->cmds[i] = malloc(ft_strlen(argv[i + 3]) * sizeof(char));
		pipex->cmds[i] = argv[i + 3];
		i++;
	}
	init_path(envp, &pipex);
}
