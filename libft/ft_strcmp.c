/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:35:48 by dalves-p          #+#    #+#             */
/*   Updated: 2022/02/07 20:23:17 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** LIBRARY: <strings.h>
** DESCRIPTION:
**		The strcmp() compares bytes of s1 and s2.
*/

int	ft_strcmp(char *s1, char *s2)
{
	int	c;

	c = 0;
	while ((unsigned char)s1[c] == (unsigned char)s2[c]
		&& (unsigned char)s1[c] != '\0' && (unsigned char)s2[c] != '\0')
	{
		c++;
	}
	return ((unsigned char)s1[c] - (unsigned char)s2[c]);
}
