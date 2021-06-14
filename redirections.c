/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:15:41 by gamirjan          #+#    #+#             */
/*   Updated: 2021/06/05 16:02:45 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_file(t_process *pr)
{
	pr->is_process = 0;
	if (pr->lsep == 2)
		pr->file_d = open(pr->pr[0], O_RDONLY, 0644);    //esi < hamara
	else if (pr->lsep == 3)
		pr->file_d = open(pr->pr[0], O_CREAT | O_WRONLY | O_APPEND, 0644); // esi >> hamara
	else if (pr->lsep == 4)
		pr->file_d = open(pr->pr[0], O_CREAT | O_TRUNC | O_WRONLY, 0644); // esi > hamara
}

void	treat_files(t_checks *check)
{
	int i;

	i = 0;
	while (i < check->argc)
	{
		if(check->coms[i].lsep >= 2)
			create_file(&check->coms[i]);
		i++;
	}

}
