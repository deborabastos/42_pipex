/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:55:01 by dalves-p          #+#    #+#             */
/*   Updated: 2022/01/18 18:38:27 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	error(char *err, int code)
{
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	exit (code);
}

char	**get_full_path(char *envp[])
{
	char	*env_paths;
	char	*full_path;
	char	**ptr_paths;

	while (*envp)
	{
		if (ft_strstr(*envp, "PATH") != 0)
			env_paths = *envp;
		envp++;
	}
	full_path = ft_strtrim(env_paths, "PATH=");
	ptr_paths = ft_split_pipex(full_path, ':');
	free(full_path);
	return (ptr_paths);
}
