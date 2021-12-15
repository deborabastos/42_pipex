/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 22:15:17 by dalves-p          #+#    #+#             */
/*   Updated: 2021/12/15 21:41:30 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** LIBRARY: N/A
** DESCRIPTION:
**		The ft_count_words() counts how many words has a string.
*/

size_t	ft_count_words(char const *s, char c)
{
	size_t	words;

	words = 0;
	if (*s != c && *s)
	{
		s++;
		words++;
	}
	while (*s != '\0')
	{
		while (*s == c && *(s + 1) != '\0')
		{
			s++;
			if (*s != c)
				words++;
		}
		s++;
	}
	return (words);
}
