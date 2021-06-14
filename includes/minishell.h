/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:21:29 by gamirjan          #+#    #+#             */
/*   Updated: 2021/06/13 01:28:29 by tharutyu         ###   ########.fr       */
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

int g_err;

typedef	struct	s_process
{
	char	**pr; //process name
	int		fd[2]; //input output for pipe
	int		file_d;
	char	is_process;
	char	lsep; //left seperator
	char	rsep; //right seperator 
}				t_process;

typedef struct	s_checks
{
	int			argc;
	int			fd[2];
	pid_t		pid;
	int			is_process; //stuguma arajin barna te che
	int			quote; //stuguma ' baca te che
	int			dquote; //stuguma " baca te che
	int			rtn;
	int			index; //petqa vor haskananq parsingi vaxt ura hasel
	int			is_child;
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
int 	to_error(t_checks *check, int p);
void 	init_envp(char **envp, t_checks *check);
int 	ft_var_len(char *str, char c);
void	ft_change_pwd(t_checks *check, char *buff);
char 	**find_path(t_checks *check);
char 	**ft_delete_env_var(int k, char **env);
char 	**ft_add_env_var(char *str, char **env);
void 	init_envp(char **envp, t_checks *check);
int		ft_export_char(int c);
void	create_file(t_process *pr);
void	treat_files(t_checks *check);
void	zero_checks(t_checks *check);
void	parse_args(t_checks *check, char *line);
void	get_process(char *line, int n, t_checks *check, int j);
int		word_count_base(char *line, t_checks *check, char *base, int num);
int		arg_count_base(char *line, t_checks *check, char *base);
int		ft_give_sep(char *str, t_checks *check, int j);
void 	ft_trim_quotes(char **str1, t_checks *check);
int		ft_get_var(char **envp, char *str, char **buff);
int		ft_check_rtn(char *str, char **buff);
int 	ft_word_len(char *line);
void	check_sep(char *buff, t_checks *check, int p);
char 	*ft_strjoini_gev(char const *s1, char const *s2);

#endif
