/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:41:37 by tharutyu          #+#    #+#             */
/*   Updated: 2021/03/30 20:55:17 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	char			*s;

	i = ft_strlen(s1);
	j = 0;
	while (j < i)
		if (ft_check_char(set, s1[j]))
			j++;
		else
			break ;
	s1 += j;
	if (*s1)
		if (!(i = ft_strlen(s1) - 1))
			return (0);
	j = 0;
	while (j <= i)
		if (ft_check_char(set, s1[i]))
			i--;
		else
			break ;
	s = malloc(i + 1);
	ft_strlcpy(s, s1, i + 2);
	return (s);
}
