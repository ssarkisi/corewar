/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_st_sti.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:32:38 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 15:21:00 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		handle_ind_sec(t_field *field, t_process *process,\
								int32_t arg1, int32_t arg2)
{
	arg2 = get_handled_index(process, arg2, IDX_MOD);
	write_to_memory_4_bytes(field->map, arg2, arg1);
	write_color(field, arg2, process->color);
}

void			ft_st(t_field *field, t_process *process)
{
	unsigned	iter;
	int32_t		arg1;
	int32_t		arg2;

	process->cur_cmd = ST;
	if (cycles_waiting(process))
	{
		iter = 2;
		arg1 = get_first_param(field, process, &iter, BIG_DIR);
		arg2 = get_sec_param(field, process, &iter, BIG_DIR);
		if (ft_is_nonvalid_st(field->map, process))
		{
			process->pos = (process->pos + iter) % MEM_SIZE;
			process->cur_cmd = FREE_CMD;
			return ;
		}
		arg1 = read_from_memory_4_bytes(process->registers[arg1 - 1], 0);
		if (IS_T_REG_SECOND(field->map[(process->pos + 1) % MEM_SIZE]))
			write_to_memory_4_bytes(process->registers[arg2 - 1], 0, arg1);
		else if (IS_T_IND_SECOND(field->map[(process->pos + 1) % MEM_SIZE]))
			handle_ind_sec(field, process, arg1, arg2);
		process->pos = (process->pos + iter) % MEM_SIZE;
		process->cur_cmd = FREE_CMD;
	}
}

static void		handle_params_sti(t_field *field, t_process *process,\
									int32_t *arg2, int32_t *arg3)
{
	if (IS_T_REG_SECOND(field->map[(process->pos + 1) % MEM_SIZE]))
		*arg2 = read_from_memory_4_bytes(process->registers[*arg2 - 1], 0);
	if (IS_T_REG_THIRD(field->map[(process->pos + 1) % MEM_SIZE]))
		*arg3 = read_from_memory_4_bytes(process->registers[*arg3 - 1], 0);
	if (IS_T_DIR_SECOND(field->map[(process->pos + 1) % MEM_SIZE]))
		*arg2 = (int16_t)(*arg2);
	if (IS_T_DIR_THIRD(field->map[(process->pos + 1) % MEM_SIZE]))
		*arg3 = (int16_t)(*arg3);
	if (IS_T_IND_SECOND(field->map[(process->pos + 1) % MEM_SIZE]))
	{
		*arg2 = get_handled_index(process, *arg2, IDX_MOD);
		*arg2 = read_from_memory_4_bytes(field->map, *arg2);
	}
	*arg2 = get_handled_index(process, *arg2 + *arg3, IDX_MOD);
}

void			ft_sti(t_field *field, t_process *process)
{
	unsigned	iter;
	int32_t		arg2;
	int32_t		arg3;
	int8_t		reg;

	process->cur_cmd = STI;
	if (cycles_waiting(process))
	{
		iter = 2;
		reg = get_first_param(field, process, &iter, SMALL_DIR);
		arg2 = get_sec_param(field, process, &iter, SMALL_DIR);
		arg3 = get_third_param(field, process, &iter, SMALL_DIR);
		if (ft_is_nonvalid_sti(field->map, process))
		{
			process->pos = (process->pos + iter) % MEM_SIZE;
			process->cur_cmd = FREE_CMD;
			return ;
		}
		handle_params_sti(field, process, &arg2, &arg3);
		write_to_memory_4_bytes(field->map, arg2,
				read_from_memory_4_bytes(process->registers[reg - 1], 0));
		write_color(field, arg2, process->color);
		process->pos = (process->pos + iter) % MEM_SIZE;
		process->cur_cmd = FREE_CMD;
	}
}
