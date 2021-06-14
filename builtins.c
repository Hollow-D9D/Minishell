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
	int fd;

	fl = 0;
	fd = 1;
	i = p + 1;
	printf("%d\n", check->argc);
	while (i < check->argc && !check->coms[i].is_process)
	{
		fd = dup(check->coms[i].file_d);
		i++;
	}
	write(fd, buff, ft_strlen(buff));
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

int to_cd(t_checks *check, int p)
{
	int 	i;
	char 	buff[1024];
	char   	*str;
	char  	*temp;

	i = 0;
	while (check->env[i] && ft_strncmp("HOME=", check->env[i], 5))
			i++;
	if (check->coms[p].pr[1] == NULL) 
	{
		if(!check->env[i])
		{
			g_err = 1;
			return (printf("minishell: %s: HOME not set\n", check->coms[p].pr[0]));
		}
		if (chdir(check->env[i] + 5) != 0)
    	{
      		g_err = 1;
      		printf("minishell: %s %s No such file or directory\n", check->coms[p].pr[0], check->env[i] + 5);
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
      		g_err = 1;
      		printf("minishell: %s %s No such file or directory\n", check->coms[p].pr[0], check->coms[p].pr[1]);
   		}
  	}
  	getcwd(buff, 1024);
  	ft_change_pwd(check, buff);
  	return (0);
}
