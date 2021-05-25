/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:21:29 by gamirjan          #+#    #+#             */
/*   Updated: 2021/05/25 12:31:50 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>

#define SPACES "\t\r\v\f \0"
#define SEPERATORS "><|;"

typedef	struct	s_process
{
	char	**pr; //process name
	int		fd[2]; //input output for pipe
	char	lsep; //left seperator
	char	rsep; //right seperator 
	int		rtnv; //process return value
}				t_process;

typedef struct	s_checks
{
	int			argc;
	int			is_process; //stuguma arajin barna te che
	int			quote; //stuguma ' baca te che
	int			dquote; //stuguma " baca te che
	int			pipe; //stuguma | ka te che ??
	int			scolon; //stuguma ; ka te che ??
	int			great; //stuguma > ka te che ??
	int			less; //stuguma < ka te che ??
	int			redir; //stuguma >> ka te che??
	int			index; //petqa vor haskananq parsingi vaxt ura hasel
	t_process	*coms; //mer commandnerna 
	char		**env; //mer popoxakannerna $
}				t_checks;

int 	main(int argc, char **argv, char **envp);
void 	my_int(int number);
void 	my_quit(int number);
int 	to_cd(t_checks *check);
int 	to_exit(t_checks *check);
int 	to_pwd(t_checks *check);
int 	to_echo(t_checks *check);
int 	to_env(t_checks *check);
int 	to_export(t_checks *check);
int 	to_unset(t_checks *check);

#endif
