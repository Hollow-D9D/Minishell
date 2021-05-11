/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:08:53 by tharutyu          #+#    #+#             */
/*   Updated: 2021/01/25 02:08:14 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memchr(const void *s, int c, size_t n)
{
	unsigned		int		i;
	unsigned		char	c1;
	const unsigned	char	*src;

	c1 = (unsigned char)c;
	src = s;
	i = 0;
	while (i < n)
	{
		if (src[i] == c1)
		{
			return (void*)(src + i);
		}
		i++;
	}
	return (0);
}
