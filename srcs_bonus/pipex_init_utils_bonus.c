/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:06:24 by coder             #+#    #+#             */
/*   Updated: 2022/02/09 18:10:57 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static void	env_to_path(char *envp[], t_pipex *pipex)
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

static void	split_cmd(char *argv[], t_pipex *pipex, int n)
{
	int	i;

	i = 0;
	while (i < pipex->count_cmds)
	{
		pipex->cmds[i] = malloc(ft_strlen(argv[i + n]) * sizeof(char));
		pipex->cmds[i] = argv[i + n];
		i++;
	}	
}

void	init(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	pipex->argc = argc;
	pipex->count_cmds = argc - 3;
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->here_doc = 0;
	pipex->limiter = 0;
	pipex->cmds = malloc(pipex->count_cmds * sizeof(char *));
	split_cmd(argv, pipex, 2);
	env_to_path(envp, pipex);
}

void	init_here_doc(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	pipex->argc = argc;
	pipex->count_cmds = argc - 4;
	pipex->infile = 0;
	pipex->outfile = argv[argc - 1];
	pipex->here_doc = 1;
	pipex->limiter = argv[2];
	pipex->cmds = malloc(pipex->count_cmds * sizeof(char *));
	split_cmd(argv, pipex, 3);
	env_to_path(envp, pipex);
}
