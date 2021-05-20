/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:06:41 by tharutyu          #+#    #+#             */
/*   Updated: 2021/01/25 02:07:08 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_bzero(void *s, size_t len)
{
	size_t			length;
	unsigned char	*str;

	str = s;
	length = 0;
	while (length < len)
	{
		str[0] = 0;
		length++;
		str++;
	}
}
