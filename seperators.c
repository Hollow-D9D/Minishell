/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamirjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:28:47 by gamirjan          #+#    #+#             */
/*   Updated: 2021/06/06 11:28:49 by gamirjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		ft_check_rtn(char *str, char **buff, t_checks *check)
{
	char *tmp;

	if (str[1] == '?')
	{
		tmp = ft_itoa(check->rtn);
		*buff = ft_strjoin(*buff, tmp);
		free (tmp);
		return (2);
	}
	else
		return (0);
}

int		ft_get_var(char **envp, char *str, char **buff)
{
	int i;
	int z;
	char *tmp;

	i = 1;
	//	if(ft_isdigit(str[i]))
		//error;
	while(ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if(i == 1)
		*buff = ft_strjoin(*buff, "$");
	if(i == 1)
		return(1);
	tmp = malloc(sizeof(char) * (i + 1));
	tmp = ft_substr(str, 1, i - 1);
	tmp = ft_strjoin(tmp, "=");
	z = 0;
	while(envp[z])
	{
		if(!ft_strncmp(tmp, envp[z], i))
		{
			free(tmp);
			tmp = ft_strdup(envp[z] + i);
			break;
		}
		z++;
	}
	if(envp[z])
		*buff = ft_strjoin(*buff, tmp);
	free(tmp);
	return (i);
}

void ft_trim_quotes(char **str1, t_checks *check) //done test ara vorovhetev trucik em nayel, norme chi ancnum mek el
{
	int i;
	char *buff;
	char *tmp;
	char *str;

	str = *str1;
	i = 0;
	tmp = malloc(sizeof(char) * 2);
	tmp[1] = '\0';
	buff = malloc(sizeof(char));
	buff[0] = '\0';
	while(str[i])
	{
		if(!check->dquote && str[i] == '\'')
		{
			check->quote = !check->quote;
			i++;
			continue;
		}
		if(!check->quote && str[i] == '\"')
		{
			check->dquote = !check->dquote;
			i++;
			continue;
		}
		// printf("c: %c  q: %d\n", str[i], check->quote);
		if((str[i] == '$') && !check->quote)
		{
			if(ft_check_rtn(str + i, &buff, check) == 2)
				i += 2;
			else
				i += ft_get_var(check->env, str + i, &buff);
			continue ;
		}
		tmp[0] = str[i];
		buff = ft_strjoin(buff, tmp);
		i++;
	}
	free(tmp);
	free(*str1);
	*str1 = ft_strdup(buff);
	free(buff);
}

int		ft_give_sep(char *str, t_checks *check, int j) // ; null = 0 >> = 3 > = 4 | = 1 < = 2 
{
	if ((str[0] != '>' && ft_check_char(SEPERATORS, str[1])))
	{
		printf("syntax error near unexpected token %c\n", str[0]);
		return (1);
	}
	if (str[0] == ';' || !str[0])
		check->coms[j].rsep = 0;
	else if (str[0] == '>' && str[1] == '>')
		check->coms[j].rsep = 3;
	else if (str[0] == '>')
		check->coms[j].rsep = 4;
	else if (str[0] == '|')
		check->coms[j].rsep = 1;
	else if (str[0] == '<')
		check->coms[j].rsep = 2;
	if ((j + 1) != check->argc)
		check->coms[j + 1].lsep = check->coms[j].rsep;
	return (0);

}
