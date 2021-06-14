/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:26:29 by gamirjan          #+#    #+#             */
/*   Updated: 2021/06/13 01:27:43 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		arg_count_base(char *line, t_checks *check, char *base)  //complete I think, stuguma qani process es pass arel
{
	int i;
	int n;
	int flag;

	flag = 0;
	n = 1;
	i = 0;
	while (line[i])
	{
		if (!check->dquote && line[i] == '\'')  //quote-handled
			check->quote = !check->quote;
		if (!check->quote && line[i] == '\"')
			check->dquote = !check->dquote;
		if (!check->dquote && !check->quote)
		{
			while (ft_check_char(base, line[i]))
			{
				flag = 1;
				i++;
			}
			if (flag)
				n++;
			flag = 0;
		}
		i++;
	}
	return (n);
}

int		word_count_base(char *line, t_checks *check, char *base, int num)  //complete I think. Word count
{
	int i;
	int n;

	n = 1;
	i = 0;
	while (i < num)
	{
		if (!check->dquote && line[i] == '\'')  //quote-handled
			check->quote = !check->quote;
		if (!check->quote && line[i] == '\"')
			check->dquote = !check->dquote;
		if (!check->dquote && !check->quote)
		{
			if (ft_check_char(base, line[i]))
			{
				n++;
				while (line[i] && ft_check_char(base, line[i]))
					i++;
				if (i == num)
					n--;
				continue ;
			}
		}
		i++;
	}
	return (n);
}

int			get_process(char *line, int n, t_checks *check, int j)
{
	int i;
	int num;
	int z;

	num = 0;
	i = check->index;
	while (ft_check_char(SPACES, line[i]))
		i++;
	num = word_count_base(line + i, check, SPACES, n - i);
	check->coms[j].pr = malloc(sizeof(char *) * (num + 1));
	check->coms[j].pr[num] = NULL;
	z = 0;
	check->coms[j].is_process = 1;
	while(z < num)
	{
		while (ft_check_char(SPACES, line[i]))
			i++;
		check->coms[j].pr[z] = ft_substr(line, i, ft_word_len(line + i));
		ft_trim_quotes(&check->coms[j].pr[z], check);
		i += ft_word_len(line + i);
		z++;
	}
	if(ft_give_sep(line + n, check, j))
		return (1);
	return (0);
}

char *check_last_semicolon(char *line)
{
	int n;
	char *tmp;

	n = ft_strlen(line) - 1;
	while(!ft_check_char(";", line[n]))
	{
		if(!ft_check_char(SPACES, line[n]))
			return (line);
		n--;
	}
	tmp = ft_substr(line, 0, n);
	return (tmp);
}

int		parse_args(t_checks *check, char *line)
{
	int i;
	int j;

	i = -1;
	j = 0;
	line = check_last_semicolon(line);
	check->argc = arg_count_base(line, check, SEPERATORS); //malloci hamar petqa vor imanas qani processi tegh es bacum
	check->coms = ft_calloc(sizeof(t_process), check->argc);
	while (line[++i])  //anavarta der mtacum em sra vra
	{
		if(!check->dquote && line[i] == '\'')  //quote-handled
			check->quote = !check->quote;
		if(!check->quote && line[i] == '\"')
			check->dquote = !check->dquote;
		if(!check->dquote && !check->quote && ft_check_char(SEPERATORS, line[i])) // seperatori conditionna test arac chi
		{
			if(get_process(line, i, check, j)) //veradarcnuma tiv vor i-n iran chkorcni
				return (1);
			j++; //processneri indexna
			while(ft_check_char(SEPERATORS, line[i]))
				i++;
			check->index = i;
			continue ;
		}
	}
	if(get_process(line, i, check, j))
		return (1);
	return (0);
}


void	zero_checks(t_checks *check)
{
	check->index = 0;
	check->argc = 0;
	check->is_process = 0;
	check->quote = 0;
	check->dquote = 0;
	check->is_child = 0;
	check->pid = 0;
}
