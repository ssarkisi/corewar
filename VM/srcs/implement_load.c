/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_load.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 15:23:52 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 15:23:53 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			ft_indirect_load(t_field *field, t_process *process,\
												int16_t idx_mod)
{
	unsigned	iter;
	int32_t		val;
	int8_t		reg;

	iter = 2;
	val = get_first_param(field, process, &iter, BIG_DIR);
	reg = get_sec_param(field, process, &iter, BIG_DIR);
	if (ft_is_nonvalid_ld(field->map, process))
	{
		process->pos = (process->pos + iter) % MEM_SIZE;
		return ;
	}
	if (IS_T_IND_FIRST(field->map[(process->pos + 1) % MEM_SIZE]))
	{
		val = get_handled_index(process, val, idx_mod);
		val = read_from_memory_4_bytes(field->map, val);
	}
	write_to_memory_4_bytes(process->registers[reg - 1], 0, val);
	if (read_from_memory_4_bytes(process->registers[reg - 1], 0) == 0)
		process->carry = TRUE;
	else
		process->carry = FALSE;
	process->pos = (process->pos + iter) % MEM_SIZE;
}

/*
** for correction-VM (it works wrong - read not 4 bytes, but 2)
*/

void			ft_indirect_load2(t_field *field, t_process *process,\
												int16_t idx_mod)
{
	unsigned	iter;
	int32_t		val;
	int8_t		reg;

	iter = 2;
	val = get_first_param(field, process, &iter, BIG_DIR);
	reg = get_sec_param(field, process, &iter, BIG_DIR);
	if (ft_is_nonvalid_ld(field->map, process))
	{
		process->pos = (process->pos + iter) % MEM_SIZE;
		return ;
	}
	if (IS_T_IND_FIRST(field->map[(process->pos + 1) % MEM_SIZE]))
	{
		val = get_handled_index(process, val, idx_mod);
		val = read_from_memory_2_bytes(field->map, val);
	}
	write_to_memory_4_bytes(process->registers[reg - 1], 0, val);
	if (read_from_memory_4_bytes(process->registers[reg - 1], 0) == 0)
		process->carry = TRUE;
	else
		process->carry = FALSE;
	process->pos = (process->pos + iter) % MEM_SIZE;
}

void			ft_ld(t_field *field, t_process *process)
{
	process->cur_cmd = LD;
	if (cycles_waiting(process))
	{
		ft_indirect_load(field, process, IDX_MOD);
		process->cur_cmd = FREE_CMD;
	}
}

void			ft_lld(t_field *field, t_process *process)
{
	process->cur_cmd = LLD;
	if (cycles_waiting(process))
	{
		ft_indirect_load2(field, process, 0);
		process->cur_cmd = FREE_CMD;
	}
}
