/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:22:20 by coder             #+#    #+#             */
/*   Updated: 2022/02/09 17:33:53 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	run_here_doc(t_pipex pipex)
{
	int		tmp_fd[2];
	char	*line;

	if (pipe(tmp_fd) == -1)
		error("Error while calling pipe", EXIT_FAILURE);
	write(STDOUT_FILENO, "pipex heredoc> ", 15);
	ft_gnl(STDIN_FILENO, &line);
	while (line && (ft_strcmp(line, pipex.limiter) != 0))
	{
		write(tmp_fd[FD_W], line, ft_strlen(line));
		write(tmp_fd[FD_W], "\n", 1);
		free(line);
		write(STDOUT_FILENO, "pipex heredoc> ", 15);
		ft_gnl(STDIN_FILENO, &line);
	}
	if (line != NULL)
		free(line);
	dup2(tmp_fd[FD_R], STDIN_FILENO);
	close(tmp_fd[FD_R]);
	close(tmp_fd[FD_W]);
	return (0);
}
