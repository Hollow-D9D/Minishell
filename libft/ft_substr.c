/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araramya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:00:54 by araramya          #+#    #+#             */
/*   Updated: 2021/02/04 13:19:48 by araramya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;

	if (!s)
		return (NULL);
	if (!(sub_str = malloc(sizeof(*s) * len + 1)))
		return (NULL);
	i = 0;
	while (*s && i < len && start < ft_strlen(s))
	{
		sub_str[i] = s[start];
		start++;
		i++;
	}
	sub_str[i] = 0;
	return (sub_str);
}
