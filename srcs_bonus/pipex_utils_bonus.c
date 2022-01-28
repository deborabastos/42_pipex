/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:55:01 by dalves-p          #+#    #+#             */
/*   Updated: 2022/01/28 01:41:56 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	error(char *err, int code)
{
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	exit (code);
}

char	**get_cmd(char *cmds)
{
	char	**cmd;
	int		i;

	cmd = ft_split_pipex(cmds, ' ');
	if (cmd[0] == NULL)
		error("command not found", 127);	
	i = 0;
	while (cmd[i])
	{
		if (ft_strstr(cmd[i], "'") != 0)
		{
			cmd[i] = ft_strtrim(cmd[i], "'");
		}
		i++;
	}
	return (cmd);
}

char	*get_path(char **ptr_paths, char *cmd)
{
	char	*ptr_path;
	char	*selected_path;
	int		i;

	i = -1;
	while (ptr_paths[++i])
	{
		ptr_path = ft_strjoin(ptr_paths[i], SEPARATOR);
		free(ptr_paths[i]);
		selected_path = ft_strjoin(ptr_path, cmd);
		free(ptr_path);
		if (access(selected_path, F_OK) == 0)
		{
			while (ptr_paths[i++] != NULL)
				free(ptr_paths[i]);
			free(ptr_paths);
			return (selected_path);			
		}
		free(selected_path);
	}
	free(ptr_paths[i]);
	free(ptr_paths);
	return (cmd);
}
