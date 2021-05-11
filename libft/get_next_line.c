/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 02:00:55 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 02:01:32 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_next_line(int fd, char **line)
{
	int		i;
	int		n;
	char	c;
	char	*str;

	i = 0;
	if (fd < 0)
		return (-1);
	if (!(str = (char*)malloc(1001)))
		return (-1);
	while ((n = read(fd, &c, 1)) && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			str[i] = c;
		++i;
	}
	str[i] = '\0';
	*line = str;
	return (n);
}
