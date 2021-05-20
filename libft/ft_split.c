/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:42:48 by tharutyu          #+#    #+#             */
/*   Updated: 2021/01/25 23:58:40 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		word_num(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue;
		}
		while (s[i] != c && s[i])
			i++;
		count++;
	}
	return (count);
}

char			**ft_split(char const *s, char c)
{
	char	**arr;
	int		i[4];

	i[0] = 0;
	i[3] = 0;
	i[1] = 0;
	arr = (char**)malloc((word_num(s, c) + 1) * sizeof(char*));
	arr[i[1]] = NULL;
	while (i[1] < word_num(s, c))
	{
		while (s[i[0]] == c)
			i[0]++;
		while (s[i[0]] != c)
		{
			i[0]++;
			i[3]++;
		}
		i[2] = 0;
		arr[i[1]] = (char*)malloc(i[3] + 1);
		while (i[3] > 0)
			arr[i[1]][i[2]++] = s[i[0] - i[3]--];
		arr[i[1]++][i[2]] = '\0';
	}
	arr[i[1]] = NULL;
	return (arr);
}
