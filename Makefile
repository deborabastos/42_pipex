# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 16:30:23 by dalves-p          #+#    #+#              #
#    Updated: 2022/02/07 20:11:31 by dalves-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	gcc
SRCS		=	srcs/pipex.c \
				srcs/pipex_utils.c \

SRCS_BONUS		=	srcs_bonus/pipex_bonus.c \
					srcs_bonus/pipex_utils_bonus.c \
					srcs_bonus/pipex_init_utils_bonus.c \

SRCS_LIB	=	libft/ft_strstr.c \
				libft/ft_strlen.c \
				libft/ft_strchr.c \
				libft/ft_strtrim.c \
				libft/ft_count_words.c \
				libft/ft_substr.c \
				libft/ft_split.c \
				libft/ft_split_pipex.c \
				libft/ft_strdup.c \
				libft/ft_strlcpy.c \
				libft/ft_strlcat.c \
				libft/ft_strjoin.c \
				libft/ft_putstr_fd.c \
				libft/ft_strcmp.c \
				libft/ft_free_ptrptr.c \
				libft/ft_gnl.c \

CFLAGS		=	-Wall -Wextra -Werror -g3
RM			=	rm -f
OBJS		=	$(SRCS:%.c=%.o)
OBJS_BONUS	=	$(SRCS_BONUS:%.c=%.o)
OBJS_LIB	=	$(SRCS_LIB:%.c=%.o)


all:		$(NAME)

$(NAME):	$(OBJS) $(OBJS_LIB)
			$(CC) $(OBJS) $(OBJS_LIB) $(CFLAGS) -o $(NAME)

bonus:		$(OBJS_BONUS) $(OBJS_LIB)
			$(CC) $(OBJS_BONUS) $(OBJS_LIB) $(CFLAGS) -o $(NAME)

clean:
			$(RM) $(OBJS) $(OBJS_LIB) $(OBJS_BONUS)

fclean:		clean
			$(RM) $(NAME)
			$(RM) *.out

oclean:		fclean
			$(RM) outfile*

re:			fclean all

git:
	@git add .
	@git commit -m "$m"
	@git push
	@echo "Commit sent to github"
# To call: make git m="my commit"