/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ptrptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 21:04:23 by dalves-p          #+#    #+#             */
/*   Updated: 2022/01/20 16:52:22 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	LIBRARY: <>
**	DESCRIPTION:
** 		The function ft_free_ptrptr(char **cmd) will free all memory allocated in
**	a double pointer.
*/

void	ft_free_ptrptr(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i] != NULL)
	{
		free(cmd[i]);
		cmd[i] = NULL;
	}
	free(cmd);
	cmd = NULL;
}
