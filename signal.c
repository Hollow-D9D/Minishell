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

//ete miqani signall ugharkelu function enq kanchum mi faili mej programaya linum
void my_int(int number)
{
	(void)number; // why not?
	exit(0);
}

void my_hup(int number)
{
	(void)number;
	// i think close(fd)
}
void my_quit(int number)
{
	return ;
}
int main()
{
	signal(SIGINT, my_int); // ctrl + C //
	signal(SIGHUP, my_hup); // ctrl + D //
	signal(SIGQUIT, my_quit); // ctrl + \ //
	while(1) ;
	return(0);
}
