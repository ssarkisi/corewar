/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_arg.o                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssarkisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 19:04:33 by ssarkisi          #+#    #+#             */
/*   Updated: 2018/04/22 19:04:34 by ssarkisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		get_arg_size(t_ol *ol, int a)
{
	char	*tmp;

	tmp = ol->arg1;
	if (a == 2)
		tmp = ol->arg2;
	if (a == 3)
		tmp = ol->arg3;
	if (tmp == NULL)
		return (0);
	if (tmp[0] == 'r')
		return (1);
	if (tmp[0] == '%')
		return (check_dir_size(ol->opcode));
	return (2);
}

char	*get_arg(t_ol *ol, int a)
{
	if (a == 1)
		return (ol->arg1);
	if (a == 2)
		return (ol->arg2);
	if (a == 3)
		return (ol->arg3);
	return (NULL);
}

int		get_arg_type(t_ol *ol, int a)
{
	char	*tmp;

	tmp = ol->arg1;
	if (a == 2)
		tmp = ol->arg2;
	if (a == 3)
		tmp = ol->arg3;
	if (tmp == NULL)
		return (0);
	if (tmp[0] == 'r')
		return (1);
	if (tmp[0] == ':' || (tmp[0] == '%' && tmp[1] == ':'))
		return (4);
	if (tmp[0] == '%')
		return (2);
	return (3);
}

void	set_arg_val(t_ol *ol)
{
	t_ol	*tmp;

	tmp = ol;
	while (tmp)
	{
		set_val(tmp, 1);
		if (tmp->argn > 1)
			set_val(tmp, 2);
		if (tmp->argn > 2)
			set_val(tmp, 3);
		tmp = tmp->next;
	}
}
