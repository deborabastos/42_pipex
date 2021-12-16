/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:46 by dalves-p          #+#    #+#             */
/*   Updated: 2021/12/16 14:57:11 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdio.h> // TIRARRRR

# define FD_R 		0
# define FD_W 		1
# define SPACEMAN 	'#$@'

# if defined _WIN32
#  define SEPARATOR	'\\'
# else
#  define SEPARATOR	"/"
# endif

typedef struct s_pipex
{
	int		argc;
	char	**cmds;
	char	*infile;
	char	*outfile;
}	t_pipex;

int		error(char *err, int code);
char	**ft_split_pipex(char const *s, char c);
char	**get_full_path(char *envp[]);

/*
** LIBFT
*/
char	*ft_strstr(char *haystack, char *needle);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isblank(int c);
int		ft_isspace(int c);
int		ft_iscntrl(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_isgraph(int c);
int		ft_ispunct(int c);
int		ft_isxdigit(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strcat(char *dest, char *src);
char	*ft_strncat(char *dest, char *src, unsigned int nb);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
void	ft_putchar(char c);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		ft_gnl(int fd, char **line);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_fibonacci(int index);
int		ft_isprime(int nb);
int		ft_factorial(int nb);
int		ft_pow(int nb, int power);
int		ft_sqrt(int nb);
void	ft_putstr(char *s);
void	ft_putnstr(char *s, int n);
void	ft_putendl(char *s);
void	ft_putnbr(int n);
int		ft_isnegative(int n);
void	ft_swap(int *a, int *b);
void	ft_div_mod(int a, int b, int *div, int *mod);
void	ft_ultimate_div_mod(int *a, int *b);
char	*ft_strcapitalize(char *str);
char	*ft_strlowcase(char *str);
char	*ft_strupcase(char *str);
size_t	ft_count_digit(long long int n);
size_t	ft_count_words(char const *s, char c);
void	ft_putlnbr(long long int n);
char	*ft_utoa_base(unsigned int n, char *base);
char	*ft_strrev(char *str);

#endif