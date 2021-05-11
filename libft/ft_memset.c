/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:05:44 by tharutyu          #+#    #+#             */
/*   Updated: 2021/01/25 02:10:33 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memset(void *b, int c, size_t len)
{
	size_t			length;
	unsigned char	*str;

	str = b;
	length = 0;
	while (length < len)
	{
		*str = c;
		length++;
		str++;
	}
	return (b);
}
