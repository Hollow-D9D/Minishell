/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamirjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:57:15 by gamirjan          #+#    #+#             */
/*   Updated: 2021/06/11 16:57:17 by gamirjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char **find_path(t_checks *check)
{
	int i = 0;
	char *str;
	char **pth;

	pth = NULL;
	while (check->env[i])
	{
		if (ft_strncmp("PATH=", check->env[i], 5) == 0)
		{	
			str = ft_strdup(check->env[i] + 5);
			pth = ft_split(str, ':');
			break ;
		}
		i++;
	}
	return (pth);
}

