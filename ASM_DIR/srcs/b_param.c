/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_param.o                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssarkisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 17:51:02 by ssarkisi          #+#    #+#             */
/*   Updated: 2018/04/22 17:51:03 by ssarkisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		bit_to_num(int *bit)
{
	int		i;
	int		j;
	int		n;
	int		ret;

	i = 0;
	j = 0;
	n = 1;
	ret = 0;
	while (i < 8)
	{
		while (j < i)
		{
			n = n * 2;
			j++;
		}
		ret = ret + (n * bit[i]);
		j = 0;
		n = 1;
		i++;
	}
	free(bit);
	return (ret);
}

int		get_param_order(int p1, int p2, int p3)
{
	int		*bit;

	bit = ft_get_zero_arr(8);
	if (p3 == 1)
		bit[2] = 1;
	if (p3 == 16)
		bit[3] = 1;
	if (p2 == 1)
		bit[4] = 1;
	if (p2 == 16)
		bit[5] = 1;
	if (p2 == 17)
		bit[4] = 1;
	if (p2 == 17)
		bit[5] = 1;
	if (p1 == 1)
		bit[6] = 1;
	if (p1 == 16)
		bit[7] = 1;
	if (p1 == 17)
		bit[6] = 1;
	if (p1 == 17)
		bit[7] = 1;
	return (bit_to_num(bit));
}

void	get_line_code(t_ol *ol)
{
	int		i;

	i = 0;
	if (ol->argn > 1)
		ol->p_order = get_param_order(get_param_type(ol->arg1),
			get_param_type(ol->arg2), get_param_type(ol->arg3));
	else if (ol->opcode == 16)
		ol->p_order = 64;
	else
		ol->p_order = 0;
	ol->size = get_command_size(ol, 1, check_dir_size(ol->opcode), 2);
	if (ol->argn != 1 || ol->opcode == 16)
		ol->size++;
	ol->code = malloc(sizeof(int) * ol->size);
	while (i < ol->size)
	{
		ol->code[i] = 0;
		i++;
	}
}

void	set_code_param(t_ol *ol)
{
	t_ol	*tmp;

	tmp = ol;
	while (tmp != NULL)
	{
		get_line_code(tmp);
		tmp = tmp->next;
	}
}
