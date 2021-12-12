/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 20:53:06 by dalves-p          #+#    #+#             */
/*   Updated: 2021/08/20 22:19:13 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*
** LIBRARY: N/A
** DESCRIPTION:
**		The ft_split_pipex() allocates (with malloc) and returns an array of strings 
**	obtained by splitting ’s’ using the character ’c’ as a delimiter. The array 
**	must be ended by a NULL pointer.
**		It returns the array of new strings resulting from the split or NULL if 
**	the allocation fails.
*/

char	*undo_space(char *space)
{
	space[1] = ' ';
	return(space);
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
			index = i; // index recebe o início da string que sera cortada (pq só entra aqui quando i < 0)
		else if (s[i] == c && index >= 0) // entra aqui quando encontra o divisor
		{
			split[j] = ft_substr(s, index, (i - index)); // corta do index até i
			index = -1;
			j++;
		}
		i++;
	}
	split[j] = ft_substr(s, index, (i - index));
	j++;
	split[j] = NULL;
	j = 0;
	while(split[j])
	{
		if (ft_strcmp( split[j], "#$@") == 0)
		{
			printf("ENTROU %s\n", split[j]);
			split[j][0] = '\'';
			split[j][1] = ' ';
			split[j][2] = '\'';
			printf("AQUI %s\n", split[j]);
		}
		j++;
	}
	return (split);
}

char	*check_spaces(char* str)
{
	char	*ptr;

	ptr = ft_strstr(str, "' '");
	// printf("PTR %s\n", ptr);
	// printf("PTR %p\n", &ptr);
	// printf("CHAR[0] %c\n", ptr[0]);
	// printf("CHAR[1] %c\n", ptr[1]);
	// printf("CHAR[2] %c\n", ptr[2]);

	// printf("STR %s\n", str);
	// printf("STR %p\n", &str);
	// printf("STR[5] %p\n", &str[5]);
	// printf("PTR[0] %p\n", &ptr[0]);

	ptr[0] = '#';
	ptr[1] = '$';
	ptr[2] = '@';

	printf("STR %s\n", str);

	// printf("New string: %s\n", new_str);
	return (str);
}

char	**ft_split_pipex(char const *s, char c)
{
	char	**split;
	char	*scpy;

	if (!s)
		return (0);
	scpy = ft_strtrim(s, &c);
	if (!scpy)
		return (0);
	if (ft_strstr(scpy, "' '") != 0)
		scpy = check_spaces(scpy);
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
