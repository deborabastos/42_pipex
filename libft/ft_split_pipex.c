/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 20:53:06 by dalves-p          #+#    #+#             */
/*   Updated: 2022/01/18 18:23:06 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** LIBRARY: N/A
** DESCRIPTION:
**		The ft_split_pipex() allocates (with malloc) and returns an array of strings 
**	obtained by splitting ’s’ using the character ’c’ as a delimiter. The array 
**	must be ended by a NULL pointer.
**		It returns the array of new strings resulting from the split or NULL if 
**	the allocation fails.
*/

static void	undo_space(char ***split)
{
	int	i;
	int	j;

	i = -1;
	while ((*split)[++i] != NULL)
	{
		j = -1;
		while ((*split)[i][++j])
		{
			if ((*split)[i][j] == 1)
				(*split)[i][j] = ' ';
		}
	}
}

static void	check_spaces(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\'')
		{
			while ((*str)[++i] != '\'' && (*str)[i] != '\0')
			{
				if ((*str)[i] == ' ')
					(*str)[i] = 1;
			}
		}
		if ((*str)[i] == '\"')
		{
			while ((*str)[++i] != '\"' && (*str)[i] != '\0')
			{
				if (((*str)[i]) == 1)
					(*str)[i] = 1;
			}
		}
		i++;
	}
}

static char	**get_strs(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	i = 0;
	j = 0;
	index = -1;
	split = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	while (s[i] != '\0')
	{
		if (s[i] != c && index < 0)
			index = i;
		else if (s[i] == c && index >= 0)
		{
			split[j] = ft_substr(s, index, (i - index));
			index = -1;
			j++;
		}
		i++;
	}
	split[j] = ft_substr(s, index, (i - index));
	split[++j] = NULL;
	undo_space(&split);
	return (split);
}

char	**ft_split_pipex(char const *s, char c)
{
	char	**split;
	char	*scpy;
	char	set[2];

	if (!s)
		return (0);
	set[0] = c;
	set[1] = '\0';
	scpy = ft_strtrim(s, set);
	if (!scpy)
		return (0);
	check_spaces(&scpy);
	if (ft_count_words(scpy, c) == 0)
	{
		split = malloc(1 * sizeof(char *));
		split[0] = NULL;
		free(scpy);
		return (split);
	}
	split = get_strs(scpy, c);
	free(scpy);
	return (split);
}
