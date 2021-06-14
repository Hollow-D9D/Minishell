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

#include "./includes/minishell.h"

void	my_quit(int sig)
{
	int		pid;
	int		status;

	(void)sig;
	pid = waitpid(-1, &status, WNOHANG); 
	if (!pid)
	{	g_err = 131;
		write(1, "Quit: 3\n", 8);
	}
	write(1, "\b\b  \b\b", 6);
}

void	my_int(int sig)
{
	int		pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (sig == SIGINT)
	{
		g_err = 130;
		if (pid)
			write(1, "\b\b  ", 4);
		ft_putchar_fd('\n', 1);
		if (pid)
			write(1, "Shell> ", 7);
	}
}

