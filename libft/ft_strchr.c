/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:11:56 by tharutyu          #+#    #+#             */
/*   Updated: 2021/01/25 02:08:57 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (s[len])
	{
		len++;
	}
	while (i <= len)
	{
		if (s[i] == c)
		{
			return (char*)(s + i);
		}
		i++;
	}
	return (0);
}
