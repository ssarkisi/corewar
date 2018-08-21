/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_load_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 15:23:46 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 15:23:46 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			handle_ind(t_field *field, t_process *process,\
												int32_t *arg1)
{
	*arg1 = get_handled_index(process, *arg1, IDX_MOD);
	*arg1 = read_from_memory_4_bytes(field->map, *arg1);
}

unsigned			ft_indirect_load_i(t_field *field, t_process *process,\
												int16_t idx_mod)
{
	unsigned	iter;
	int32_t		arg1;
	int32_t		arg2;
	int8_t		reg;

	iter = 2;
	arg1 = get_first_param(field, process, &iter, SMALL_DIR);
	arg2 = get_sec_param(field, process, &iter, SMALL_DIR);
	reg = get_third_param(field, process, &iter, SMALL_DIR);
	if (ft_is_nonvalid_ldi(field->map, process) && (errno = NON_VALID_PARAMS))
		return (iter);
	if (IS_T_REG_FIRST(field->map[(process->pos + 1) % MEM_SIZE]))
		arg1 = read_from_memory_4_bytes(process->registers[arg1 - 1], 0);
	if (IS_T_REG_SECOND(field->map[(process->pos + 1) % MEM_SIZE]))
		arg2 = read_from_memory_4_bytes(process->registers[arg2 - 1], 0);
	if (IS_T_IND_FIRST(field->map[(process->pos + 1) % MEM_SIZE]))
		handle_ind(field, process, &arg1);
	if (IS_T_DIR_FIRST(field->map[(process->pos + 1) % MEM_SIZE]))
		arg1 = (int16_t)arg1;
	if (IS_T_DIR_SECOND(field->map[(process->pos + 1) % MEM_SIZE]))
		arg2 = (int16_t)arg2;
	arg1 = get_handled_index(process, arg1 + arg2, idx_mod);
	arg1 = read_from_memory_4_bytes(field->map, arg1);
	write_to_memory_4_bytes(process->registers[reg - 1], 0, arg1);
	return (iter);
}

void				ft_ldi(t_field *field, t_process *process)
{
	unsigned	iter;

	process->cur_cmd = LDI;
	if (cycles_waiting(process))
	{
		iter = ft_indirect_load_i(field, process, IDX_MOD);
		process->pos = (process->pos + iter) % MEM_SIZE;
		process->cur_cmd = FREE_CMD;
	}
}

void				ft_lldi(t_field *field, t_process *process)
{
	unsigned	iter;
	int8_t		reg;

	process->cur_cmd = LLDI;
	if (cycles_waiting(process))
	{
		iter = ft_indirect_load_i(field, process, 0);
		reg = field->map[(process->pos + iter - 1) % MEM_SIZE];
		if (errno != NON_VALID_PARAMS &&
				*(int32_t*)process->registers[reg - 1] == 0)
			process->carry = TRUE;
		else if (errno != NON_VALID_PARAMS)
			process->carry = FALSE;
		errno = DEFAULT_ERRNO;
		process->pos = (process->pos + iter) % MEM_SIZE;
		process->cur_cmd = FREE_CMD;
	}
}
