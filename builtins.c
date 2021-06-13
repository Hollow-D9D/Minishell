/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:28:10 by gamirjan          #+#    #+#             */
/*   Updated: 2021/06/08 00:06:17 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int to_echo(t_checks *check, int p)
{
	int i;
	int nflag;
	char *str;

	str = malloc(sizeof(char));
	str[0] = 0;
	nflag = 0;
	i = 1;
	if (check->coms[p].pr[1] && ft_strcmp(check->coms[p].pr[1], "-n") == 0)
	{
		i++;
		nflag = 1;
	}
	while(check->coms[p].pr[i])
	{
		str = ft_strjoin(str, check->coms[p].pr[i]);
		str = ft_strjoin(str, " ");
		i++;
	}
	if (!nflag)
		str = ft_strjoin(str, "\n");
	check_sep(str, check, p);
	return (0);
}

void check_sep(char *buff, t_checks *check, int p)
{
	int i;
	int fl;

	fl = 0;
	i = p;
	while (i < check->argc && !check->coms[i + 1].is_process)
	{
		if (check->coms[i + 1].lsep > 2)
		{
			write(check->coms[i + 1].file_d, buff, ft_strlen(buff));
			fl = 1;
		}
		else if (!fl)
		{
			write(1, buff, ft_strlen(buff));
			fl = 1;
		}
		i++;
	}
	if (i == p && !fl)
		write(1, buff, ft_strlen(buff));
	return ;
}

int to_pwd(t_checks *check, int p)
{
	int i;

	(void)check;
	char buffer[1024];
	getcwd(buffer, 1024);
	i = ft_strlen(buffer);
	buffer[i] = '\n';
	buffer[++i] = '\0';
	check_sep(buffer, check, p);
	return (0);
}

int to_exit(t_checks *check, int p)
{
	(void)check;
	p = 0;
	if (check->coms[p].pr[1])
	{
		p = ft_atoi(check->coms[p].pr[1]);
	}
	printf("%d\n", p);
	exit(p);
}

void	ft_change_pwd(t_checks *check, char *buff)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	while(check->env[i] && ft_strncmp("PWD=", check->env[i], 4))
		i++;
	while(check->env[j] && ft_strncmp("OLDPWD=", check->env[j], 7))
		j++;
	if (check->env[i] && check->env[j])
	{
		free(check->env[j]);
		check->env[j] = ft_strdup("OLDPWD=");
		check->env[j] = ft_strjoin(check->env[j], check->env[i]);
	}
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
		check->env = ft_add_env_var(tmp, check->env);
	}
}
/// verjum ete ; ka eti ok a
int to_cd(t_checks *check, int p)
{
	int 	i;
	char 	buff[1024];
	char   	*str;
	char  	*temp;

	i = 0;
	if (check->coms[p].pr[1])
		printf("PROCESS 1 NAME==%s\n", check->coms[p].pr[1]);
	if (check->coms[p].pr[2])
		printf("PROCESS 2 KA\n");
	else 
		printf("CHKA\n");
	while (check->env[i] && ft_strncmp("HOME=", check->env[i], 5))
			i++;
	if (check->coms[p].pr[1] == NULL) 
	{
		if(!check->env[i])
			return (printf("NO HOME\n"));
		if (chdir(check->env[i] + 5) != 0) 
    	{
      		perror("xi araaaaa");
   		}
  	}
	else 
	{
		if (check->coms[p].pr[1][0] == '~')
		{
   			temp = ft_strdup(check->coms[p].pr[1] + 1);
   			str = ft_strjoini_gev(check->env[i] + 5, temp);
   			chdir(str);
   			free(str);
		}
		else if (chdir(check->coms[p].pr[1]) != 0) 
    	{
      		perror("NOOOO");
   		}
  	}
  	getcwd(buff, 1024);
  	ft_change_pwd(check, buff);
  	return (0);
}
