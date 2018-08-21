/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_conds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:32:13 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:32:15 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		init_args(t_field *field, t_process *process,
							int32_t *val1, int32_t *val2)
{
	if (IS_T_REG_FIRST(field->map[(process->pos + 1) % MEM_SIZE]))
		*val1 = read_from_memory_4_bytes(process->registers[*val1 - 1], 0);
	if (IS_T_REG_SECOND(field->map[(process->pos + 1) % MEM_SIZE]))
		*val2 = read_from_memory_4_bytes(process->registers[*val2 - 1], 0);
	if (IS_T_IND_FIRST(field->map[(process->pos + 1) % MEM_SIZE]))
	{
		*val1 = get_handled_index(process, *val1, IDX_MOD);
		*val1 = read_from_memory_4_bytes(field->map, *val1);
	}
	if (IS_T_IND_SECOND(field->map[(process->pos + 1) % MEM_SIZE]))
	{
		*val2 = get_handled_index(process, *val2, IDX_MOD);
		*val2 = read_from_memory_4_bytes(field->map, *val2);
	}
}

void			ft_and(t_field *field, t_process *process)
{
	unsigned	iter;
	int32_t		val1;
	int32_t		val2;
	int8_t		reg;

	process->cur_cmd = AND;
	if (cycles_waiting(process))
	{
		iter = 2;
		val1 = get_first_param(field, process, &iter, BIG_DIR);
		val2 = get_sec_param(field, process, &iter, BIG_DIR);
		reg = get_third_param(field, process, &iter, BIG_DIR);
		if (ft_is_nonvalid_conds(field->map, process))
		{
			process->pos = (process->pos + iter) % MEM_SIZE;
			process->cur_cmd = FREE_CMD;
			return ;
		}
		init_args(field, process, &val1, &val2);
		val1 = val1 & val2;
		write_to_memory_4_bytes(process->registers[reg - 1], 0, val1);
		process->pos = (process->pos + iter) % MEM_SIZE;
		change_carry(process, val1);
		process->cur_cmd = FREE_CMD;
	}
}

void			ft_or(t_field *field, t_process *process)
{
	unsigned	iter;
	int32_t		val1;
	int32_t		val2;
	int8_t		reg;

	process->cur_cmd = OR;
	if (cycles_waiting(process))
	{
		iter = 2;
		val1 = get_first_param(field, process, &iter, BIG_DIR);
		val2 = get_sec_param(field, process, &iter, BIG_DIR);
		reg = get_third_param(field, process, &iter, BIG_DIR);
		if (ft_is_nonvalid_conds(field->map, process))
		{
			process->pos = (process->pos + iter) % MEM_SIZE;
			process->cur_cmd = FREE_CMD;
			return ;
		}
		init_args(field, process, &val1, &val2);
		val1 = val1 | val2;
		write_to_memory_4_bytes(process->registers[reg - 1], 0, val1);
		process->pos = (process->pos + iter) % MEM_SIZE;
		change_carry(process, val1);
		process->cur_cmd = FREE_CMD;
	}
}

void			ft_xor(t_field *field, t_process *process)
{
	unsigned	iter;
	int32_t		val1;
	int32_t		val2;
	int8_t		reg;

	process->cur_cmd = XOR;
	if (cycles_waiting(process))
	{
		iter = 2;
		val1 = get_first_param(field, process, &iter, BIG_DIR);
		val2 = get_sec_param(field, process, &iter, BIG_DIR);
		reg = get_third_param(field, process, &iter, BIG_DIR);
		if (ft_is_nonvalid_conds(field->map, process))
		{
			process->pos = (process->pos + iter) % MEM_SIZE;
			process->cur_cmd = FREE_CMD;
			return ;
		}
		init_args(field, process, &val1, &val2);
		val1 = val1 ^ val2;
		write_to_memory_4_bytes(process->registers[reg - 1], 0, val1);
		process->pos = (process->pos + iter) % MEM_SIZE;
		change_carry(process, val1);
		process->cur_cmd = FREE_CMD;
	}
}
