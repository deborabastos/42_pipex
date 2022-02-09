/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:46 by dalves-p          #+#    #+#             */
/*   Updated: 2022/02/07 20:17:24 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdio.h> // TIRARRRR

# define FD_R 		0
# define FD_W 		1

# if defined _WIN32
#  define SEPARATOR	'\\'
# else
#  define SEPARATOR	"/"
# endif

# define OPEN_MAX		255

typedef struct s_pipex
{
	int		argc;
	int		count_cmds;
	char	**cmds;
	char	*infile;
	char	*outfile;
	char	**paths;
	int		here_doc;
	char	*limiter;
}	t_pipex;

/*
** FUNCTIONS PROTOTYPE
*/

int		error(char *err, int code);
char	**get_cmd(char *cmds);
char	*get_path(char **ptr_paths, char *cmd);
void	init(int argc, char *argv[], char *envp[], t_pipex *pipex);
void	init_here_doc(int argc, char *argv[], char *envp[], t_pipex *pipex);


/*
** LIBFT
*/

size_t	ft_count_words(char const *s, char c);
void	ft_free_ptrptr(char **cmd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split_pipex(char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strstr(char *haystack, char *needle);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_gnl(int fd, char **line);

#endif