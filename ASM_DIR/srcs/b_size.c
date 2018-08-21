/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_size.o                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssarkisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 16:56:47 by ssarkisi          #+#    #+#             */
/*   Updated: 2018/04/24 16:56:48 by ssarkisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		get_param_type(char *arg)
{
	if (arg == NULL)
		return (0);
	if (arg[0] == 'r')
		return (1);
	if (arg[0] == '%')
		return (16);
	return (17);
}

int		get_total_code_size(t_ol *ol)
{
	t_ol		*tmp;
	int			ret;

	tmp = ol;
	ret = 0;
	while (tmp)
	{
		if (tmp->opcode == -1)
			tmp->size = 0;
		ret = ret + tmp->size;
		tmp = tmp->next;
	}
	return (ret);
}

int		check_dir_size(int n)
{
	if (n == 9 || n == 10 || n == 11 || n == 12 || n == 14 || n == 15)
		return (2);
	return (4);
}

int		get_command_size(t_ol *ol, int a1, int a2, int a3)
{
	int		size;
	int		p[3];

	p[0] = get_param_type(ol->arg1);
	p[1] = get_param_type(ol->arg2);
	p[2] = get_param_type(ol->arg3);
	size = a1;
	if (p[0] == 16)
		size = a2;
	else if (p[0] == 17)
		size = a3;
	if (p[1] == 1)
		size += a1;
	else if (p[1] == 16)
		size += a2;
	else if (p[1] == 17)
		size += a3;
	if (p[2] == 1)
		size += a1;
	else if (p[2] == 16)
		size += a2;
	else if (p[2] == 17)
		size += a3;
	return ((1 + size));
}
