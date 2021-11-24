/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-p <dalves-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:29:46 by dalves-p          #+#    #+#             */
/*   Updated: 2021/11/23 16:44:54 by dalves-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> //access, unlink, close, read, write, pipe, dup, dup2, execve, fork
# include <fcntl.h> // open
# include <stdlib.h> // malloc, free, exit
# include <sys/wait.h> // wait, waitpid
# include <errno.h> // perror
# include <string.h> // strerror

#endif