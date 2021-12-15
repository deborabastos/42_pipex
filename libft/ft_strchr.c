/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 19:16:59 by dalves-p          #+#    #+#             */
/*   Updated: 2021/12/15 19:24:51 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** LIBRARY: <strings.h>
** DESCRIPTION:
**		The strchr() function returns a pointer to the first occurrence of the 
**	character c in the string s.
**		It return a pointer to the matched character or NULL if the character is 
**	not found. The terminating null byte is considered part of the string, so 
**	that if c is specified as '\0', these functions return a pointer to the 
**	terminator.
*/

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	ch;

	str = (char *)s;
	ch = (char)c;
	while (*str != '\0')
	{
		if (*str == ch)
			return (str);
		str++;
	}
	if (*str == '\0' && ch == '\0')
		return (str);
	return (0);
}
