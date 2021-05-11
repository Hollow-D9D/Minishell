/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:08:10 by tharutyu          #+#    #+#             */
/*   Updated: 2021/01/25 02:08:10 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned		int		i;
	unsigned const	char	*s;
	unsigned		char	*d;

	s = src;
	d = dest;
	i = 0;
	while (i < n)
	{
		if (s[i] == c)
		{
			d[i] = s[i];
			return (d + i + 1);
		}
		d[i] = s[i];
		i++;
	}
	return (0);
}
