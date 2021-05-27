/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamirjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 08:09:56 by gamirjan          #+#    #+#             */
/*   Updated: 2021/05/19 08:34:38 by gamirjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void my_int(int number)
{
	(void)number; // why not?
	exit(0);
}

void my_quit(int number)
{
	(void)number;
	printf("axper taron\n\n");
}
