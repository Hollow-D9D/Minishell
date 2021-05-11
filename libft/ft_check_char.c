/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 10:58:44 by tharutyu          #+#    #+#             */
/*   Updated: 2021/03/28 10:59:23 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_check_char(char const *x, char y)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(x))
	{
		if (x[i] == y)
			return (1);
		i++;
	}
	return (0);
}
