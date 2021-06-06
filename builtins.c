/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:28:10 by gamirjan          #+#    #+#             */
/*   Updated: 2021/06/05 16:01:42 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int to_echo(t_checks *check, int p)
{
	int i;
	int nflag;

	nflag = 0;
	i = 1;
	if (!check->coms[p].pr[1])
	{
		write (check->coms[p].file_d, "\n", 1);
		return (0);
	}
	if (ft_strcmp(check->coms[p].pr[1], "-n") == 0)
	{
		i++;
		nflag = 1;
	}
	while(check->coms[p].pr[i])
	{
		write(1, check->coms[p].pr[i], ft_strlen(check->coms[p].pr[i]));
		write(check->coms[p].file_d, " ", 1);
		i++;
	}
	//my_errno(0); // read my_errno
	if (!nflag)
		write(1, "\n", 1);
	//my_errno(0); // read my_errno
	return (0);
}

void check_sep(char *buff, t_checks *check, int p)
{
	if (!check->coms[p + 1].is_process)
	{
		if (check->coms[p + 1].lsep == 4)
			write(check->coms[p + 1].file_d, buff, ft_strlen(buff));
		else if (check->coms[p + 1].lsep == 3)
			write(check->coms[p + 1].file_d, buff, ft_strlen(buff));
	}
	return ;
}

int to_pwd(t_checks *check, int p)
{
	int i;

	(void)check;
	char buffer[1024];
	getcwd(buffer, 1024);
	//printf("%s\n", buffer);
	i = ft_strlen(buffer);
	buffer[i] = '\n';
	buffer[++i] = '\0';
	check_sep(buffer, check, p);
	//my_errno(0); // read my_errno
	return (0);
}

int to_exit(t_checks *check, int p)
{
	(void)check;
	p = 0;
	exit(0);
}

void	ft_change_pwd(t_checks *check, char *buff)
{
	int i;
	char *tmp;

	i = 0;
	while(check->env[i] && ft_strncmp("PWD=", check->env[i], 4))
		i++;
	if (check->env[i])
	{
		free(check->env[i]);
		check->env[i] = ft_strdup("PWD=");
		check->env[i] = ft_strjoin(check->env[i], buff);
	}
	else
	{
		tmp = ft_strdup("PWD=");
		tmp = ft_strjoin(tmp, buff);
		//printf("%s\n", tmp);
		check->env = ft_add_env_var(tmp, check->env);
	}
}

int to_cd(t_checks *check, int p)
{
	int 	i;
	char 	buff[1024];

	i = 0;
	if (check->coms[p].pr[1] == NULL) 
	{
		while (check->env[i] && ft_strncmp("HOME=", check->env[i], 5))
			i++;
		if(!check->env[i])
			return (printf("NO HOME\n"));
		if (chdir(check->env[i] + 5) != 0) 
    	{
      		perror("lsh");
   		}
  	} 
	else 
	{
		if (chdir(check->coms[p].pr[1]) != 0) 
    	{
      		perror("lsh");
   		}
  	}
  	getcwd(buff, 1024);
  	ft_change_pwd(check, buff);
  	return (0);
}
