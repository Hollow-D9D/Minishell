/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamirjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 10:53:30 by gamirjan          #+#    #+#             */
/*   Updated: 2021/06/06 10:53:44 by gamirjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void my_errno(int err, t_checks *check)
{
	// char *str;

	check->rtn = err;
	//printf("my errno: %d\n", check->rtn);
// 	str = ft_itoa(err); 
// 	printf("%s\n", str);
// 	free (str);
}


int to_error(t_checks *check, int p)
{
	(void)p;
	char *str;

	str = malloc(1000);
	str = ft_itoa(check->rtn);
	ft_putstr("command not found: ");
	printf("%s\n", str);
	// ft_putstr_fd(get_var_param(g_params->env, "?"), 2);
	// ft_putstr_fd("\n", 2);
	free(str);
	return (1);
}

/*
inq@ voroshuma mer error number@ indz tvuma iran arji inch vor mi hat popoxakan stringi
mej pahel u an@ndhat free anel, u poxel kaxvac gorcoghutyunic, u amen angam erb $?
lini inq@ nor tpi mer errornumber@

glxavor structi mej hatuk int ka vor karanq grenq check->rtn = my_errno(err);
*/
