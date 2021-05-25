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

int to_echo(char **args);
int main(int argc, char **argv, char **envp);
void my_int(int number);
void my_quit(int number);
int to_cd(char **args);
int to_exit(char **args);
int to_pwd(char **args);
int to_env(char **args);


#endif
