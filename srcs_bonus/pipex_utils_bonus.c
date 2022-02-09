/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:55:01 by dalves-p          #+#    #+#             */
/*   Updated: 2022/02/09 17:49:52 by dalves-p         ###   ########.fr       */
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

void	close_pipes(t_pipex pipex, int pipe_fd[][2], int i)
{
	int	j;

	j = -1;
	while (++j < pipex.count_cmds + 1)
	{
		if (i != j)
			close(pipe_fd[j][FD_R]);
		if (i + 1 != j)
			close(pipe_fd[j][FD_W]);
	}
}
