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

void	my_quit(int sig) // test ara /bin/sleep[varkyan]/ hramanov u ctrl \ ara
{
	int		pid;
	int		status;

	(void)sig;
	pid = waitpid(-1, &status, WNOHANG); // -1     означает ожидать любого дочернего процесса; функция wait ведет себя точно так же.
	if (!pid)
	{	g_err = 131;							// означает вернуть управление немедленно, если ни один дочерний процесс  не  завершил выполнение.
		write(1, "Quit: 3\n", 8);
	}
}

void	my_int(int sig)
{
	int		pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (sig == SIGINT)
	{
		g_err = 130;
		ft_putchar_fd('\n', 1); // mi hat slesh ena dnum vor gna hajord togh mi hat el hajord toghum prost@ tpuma shell
		if (pid)
			write(1, "Shell> ", 7);
	}
}

