/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:21:29 by gamirjan          #+#    #+#             */
/*   Updated: 2021/06/04 15:36:44 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
	int		file_d;
	char	is_process;
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
	int			rtn;
	int			index; //petqa vor haskananq parsingi vaxt ura hasel
	t_process	*coms; //mer commandnerna 
	char		**env; //mer popoxakannerna $
}				t_checks;

int 	main(int argc, char **argv, char **envp);
void 	my_int(int number);
void 	my_quit(int number);
int 	to_cd(t_checks *check, int p);
int 	to_exit(t_checks *check, int p);
int 	to_pwd(t_checks *check, int p);
int 	to_echo(t_checks *check, int p);
int 	to_env(t_checks *check, int p);
int 	to_export(t_checks *check, int p);
int 	to_unset(t_checks *check, int p);
void 	init_envp(char **envp, t_checks *check);
int 	ft_var_len(char *str, char c);
void	ft_change_pwd(t_checks *check, char *buff);
char 	**ft_delete_env_var(int k, char **env);
char 	**ft_add_env_var(char *str, char **env);
void 	init_envp(char **envp, t_checks *check);
int		ft_export_char(int c);
void	create_file(t_process *pr);
void	treat_files(t_checks *check);

#endif
