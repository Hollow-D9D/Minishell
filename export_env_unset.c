/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:29:06 by gamirjan          #+#    #+#             */
/*   Updated: 2021/06/14 17:36:21 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char **ft_delete_env_var(int k, char **env)
{
	t_checks 	temp;
	char 		**newenv;
	int 		i; 
	int 		j;
	
	i = 0;
	j = 0;
	while(env[i])
		i++;
	init_envp(env, &temp);
	while(env[j])
	{
		free(env[j]);
		++j;
	}
	free(env);
	newenv = malloc((i + 1) * sizeof(char *));
	j = 0;
	i = 0;
	while(temp.env[j])
	{
		if(j != k)
		{
			newenv[i] = ft_strdup(temp.env[j]);
			i++;
		}
		j++;
	}
	newenv[i] = NULL;
	j = 0;
	while(temp.env[j])
	{
		free(temp.env[j]);
		++j;
	}
	free(temp.env);
	return (newenv);
}

int to_unset(t_checks *check, int p) // mer unsetn a kayfot funkcia a
{
	int i;
	int j;

	i = 1;
	if (check->coms[p].pr[1] == NULL)  // ete mi argumenta petqa es tpi
		return (0);
	else
		while (check->coms[p].pr[i])
		{
			j = 0;
			while (check->env[j])
			{
				if (!ft_strncmp(check->env[j], check->coms[p].pr[i], ft_var_len(check->env[j], '=')))
				{
					check->env = ft_delete_env_var(j, check->env);
				}
				j++;
			}
			i++;
		}	
	g_err = 0;
	return (0);
}

char **ft_add_env_var(char *str, char **env) 
{
	t_checks 	temp;
	char 		**newenv;
	int 		i; 
	int 		j;
	
	if (!ft_isalpha(str[0]) && (str[0] != '_' ))
	{
		g_err = 1;
		printf("export: not an identifier: %c\n", str[0]);
		return (env);
	}
	i = 1;
	while (str[i] != '\0' && str[i] != '=') ///ste petqa return ani het gna erkrord exportn ani voch te segfault ta 2 argumenti depqum gandon@@@
	{
		if (!ft_export_char(str[i]))
		{			
			g_err = 1;
			printf("export: not valid in this context: %s\n", str);
			return (env);
		}
		i++;
	}
	i = 0;
	j = 0;
	while(env[i])
		i++;
	i++;
	init_envp(env, &temp);
	while(env[j])
	{
		free(env[j]);
		j++;
	}
	free(env);
	newenv = malloc((i + 1) * sizeof(char *));
	j = 0;
	while(temp.env[j])
	{
		newenv[j] = ft_strdup(temp.env[j]);
		++j;
	}
	newenv[j++] = ft_strdup(str);
	newenv[j] = NULL;
	j = 0;
	while(temp.env[j])
	{
		free(temp.env[j]);
		++j;
	}
	free(temp.env);
	return (newenv);
}

int to_export(t_checks *check, int p)
{
	int i;
	int j;

	i = 1;
	g_err = 0;
	if (check->coms[p].pr[1] == NULL) // ete mi argumenta petqa env@ tpi
		return (to_env(check, p));
	else
		while (check->coms[p].pr[i])
		{
			j = 0;
			while (check->env[j])
			{
				if (!ft_strncmp(check->env[j], check->coms[p].pr[i], ft_var_len(check->env[j], '=')))
				{
					free(check->env[j]);
					check->env[j] = ft_strdup(check->coms[p].pr[i]);
					break ;
				}
				j++;
			}
			if (check->env[j])
			{
				i++;
				continue ;
			}
			check->env = ft_add_env_var(check->coms[p].pr[i], check->env);
			if (g_err == 1)
				return (1);
			else
				i++;
		}
	return (0);
}

int to_env(t_checks *check, int p) // mer envna ughaki malloci pah@ garlakhaca  output rediercted correctly inch vor anasun errora berum erb vor mi 5 hat file em talis, chgitem der inchica
{
	int i;
	i = 0;
	char *str;

	if (check->coms[p].pr[1])
	{
		g_err = 127;
		printf("minishell: %s %s No such file or directory\n", check->coms[p].pr[0], check->coms[p].pr[1]);
	}
	else
	{
		str = malloc(sizeof(char));
		str[0] = 0;
		while (check->env[i])
		{
			str = ft_strjoin(str, check->env[i]);
			str = ft_strjoin(str, "\n");
			i++;
		}
		g_err = 0;
		check_sep(str, check, p);
	}
	return (0);
}

void 	init_envp(char **envp, t_checks *check)
{
	int e;
	e = 0;

	while (envp[e])
		e++;
	check->env = malloc(sizeof(char *) * (e + 1)); /// es petqa normal malloc arvi asenq
	check->env[e] = NULL;
	e = 0;
	while (envp[e])
	{
		check->env[e] = ft_strdup(envp[e]);
		e++;
	}
}
