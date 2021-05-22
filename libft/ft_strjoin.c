/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:40:45 by tharutyu          #+#    #+#             */
/*   Updated: 2021/05/22 21:55:35 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;
	size_t	len;

	if(!s1)
		s1 = calloc(1, sizeof(char));
	len = ft_strlen(s1) + ft_strlen(s2);
	d = malloc(len + 1);
	ft_memmove(d, s1, ft_strlen(s1));
	ft_memmove(d + ft_strlen(s1), s2, ft_strlen(s2));
	d[len] = 0;
	return (d);
}
