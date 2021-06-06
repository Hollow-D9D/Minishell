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

void my_errno(int err)
{
	char *str;

	str = ft_itoa(err); 
	printf("%s\n", str);
	free (str);
}

/*
inq@ voroshuma mer error number@ indz tvuma iran arji inch vor mi hat popoxakan stringi
mej pahel u an@ndhat free anel, u poxel kaxvac gorcoghutyunic, u amen angam erb $?
lini inq@ nor tpi mer errornumber@

*/