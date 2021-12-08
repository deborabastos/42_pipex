# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 16:30:23 by dalves-p          #+#    #+#              #
#    Updated: 2021/12/07 20:54:03 by dalves-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	clang
SRCS		=	srcs/pipex.c \
				
SRCS_LIB	=	libft/ft_strstr.c \
				libft/ft_strlen.c \
				libft/ft_strchr.c \
				libft/ft_strtrim.c \
				libft/ft_count_words.c \
				libft/ft_substr.c \
				libft/ft_split.c \
				libft/ft_strdup.c \
				libft/ft_strlcpy.c \
				libft/ft_strlcat.c \
				libft/ft_strjoin.c \
				libft/ft_putstr_fd.c \

				# libft/ft_memset.c \
				# libft/ft_bzero.c \
				# libft/ft_memcpy.c \
				# libft/ft_memccpy.c
				# libft/ft_memchr.c \
				# libft/ft_memcmp.c \
				# libft/ft_memmove.c \
				# libft/ft_strcmp.c \
				# libft/ft_strncmp.c \
				# libft/ft_strcpy.c \
				# libft/ft_strncpy.c \
				# libft/ft_strcat.c \
				# libft/ft_strncat.c \
				# libft/ft_strrchr.c \
				# libft/ft_strnstr.c \
				# libft/ft_isalpha.c \
				# libft/ft_isdigit.c \
				# libft/ft_isalnum.c \
				# libft/ft_isprint.c \
				# libft/ft_isascii.c \
				# libft/ft_isblank.c \
				# libft/ft_isspace.c \
				# libft/ft_iscntrl.c \
				# libft/ft_islower.c \
				# libft/ft_isupper.c \
				# libft/ft_isgraph.c \
				# libft/ft_ispunct.c \
				# libft/ft_isxdigit.c \
				# libft/ft_atoi.c \
				# libft/ft_toupper.c \
				# libft/ft_tolower.c \
				# libft/ft_strcapitalize.c \
				# libft/ft_calloc.c \
				# libft/ft_putchar_fd.c \
				# libft/ft_putnbr_fd.c \
				# libft/ft_putnstr.c \
				# libft/ft_putendl_fd.c \
				# libft/ft_strmapi.c \
				# libft/ft_itoa.c \
				# libft/ft_lstnew.c \
				# libft/ft_lstadd_front.c \
				# libft/ft_lstsize.c \
				# libft/ft_lstadd_back.c \
				# libft/ft_lstlast.c \
				# libft/ft_lstdelone.c \
				# libft/ft_lstclear.c \
				# libft/ft_lstiter.c \
				# libft/ft_lstmap.c \
				# libft/ft_putchar.c \
				# libft/ft_putnbr.c \
				# libft/ft_putstr.c \
				# libft/ft_putendl.c \
				# libft/ft_isnegative.c \
				# libft/ft_swap.c \
				# libft/ft_div_mod.c \
				# libft/ft_ultimate_div_mod.c \
				# libft/ft_fibonacci.c \
				# libft/ft_isprime.c \
				# libft/ft_factorial.c \
				# libft/ft_pow.c \
				# libft/ft_sqrt.c \
				# libft/ft_strlowcase.c \
				# libft/ft_strupcase.c \
				# libft/ft_putlnbr.c \
				# libft/ft_utoa_base.c \
				# libft/ft_uinttoa_base.c \
				# libft/ft_strrev.c \
				# libft/ft_count_digit.c \
				# libft/ft_gnl.c \

CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f
OBJS		=	$(SRCS:%.c=%.o)
OBJS_LIB	=	$(SRCS_LIB:%.c=%.o)


all:		$(NAME)

$(NAME):	$(OBJS) $(OBJS_LIB)
			$(CC) $(SRCS) $(SRCS_LIB) $(CFLAGS) -o $(NAME)

%o:			%.c
			$(CC) $(CFLAGS) -c $< -o $@

run:		all
			./$(NAME) infile "grep Now" "wc -w" "outfile"
#			./$(NAME) infile "cat -n" "grep Talita" outfile
#			./$(NAME) infile "cat" "wc -l" outfile 

clean:
			$(RM) $(OBJS) $(OBJS_LIB)

fclean:		clean
			$(RM) $(NAME)
			$(RM) *.out

re:			fclean all

git:
	@git add .
	@git commit -m "$m"
	@git push
	@echo "Commit sent to github"
# To call: make git m="my commit"