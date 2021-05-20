/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:08:32 by tharutyu          #+#    #+#             */
/*   Updated: 2021/01/25 02:08:29 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned		int		i;
	unsigned const	char	*s;
	unsigned		char	*d;
	unsigned		char	buff[len];

	s = src;
	d = dest;
	i = 0;
	while (i < len)
	{
		buff[i] = s[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		d[i] = buff[i];
		i++;
	}
	return (dest);
}
