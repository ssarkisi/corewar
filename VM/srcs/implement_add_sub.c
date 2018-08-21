/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_add_sub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 16:47:15 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 16:47:16 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		init_regs(t_process *process, int32_t *reg1, int32_t *reg2)
{
	*reg1 = read_from_memory_4_bytes(process->registers[*reg1 - 1], 0);
	*reg2 = read_from_memory_4_bytes(process->registers[*reg2 - 1], 0);
}

void			ft_add(t_field *field, t_process *process)
{
	unsigned	iter;
	int32_t		reg1;
	int32_t		reg2;
	int8_t		reg3;

	process->cur_cmd = ADD;
	if (cycles_waiting(process))
	{
		iter = 2;
		reg1 = get_first_param(field, process, &iter, BIG_DIR);
		reg2 = get_sec_param(field, process, &iter, BIG_DIR);
		reg3 = get_third_param(field, process, &iter, BIG_DIR);
		if (ft_is_nonvalid_addsub(field->map, process))
		{
			process->pos = (process->pos + iter) % MEM_SIZE;
			process->cur_cmd = FREE_CMD;
			return ;
		}
		init_regs(process, &reg1, &reg2);
		write_to_memory_4_bytes(process->registers[reg3 - 1], 0, reg1 + reg2);
		process->pos = (process->pos + iter) % MEM_SIZE;
		change_carry(process,
			read_from_memory_4_bytes(process->registers[reg3 - 1], 0));
		process->cur_cmd = FREE_CMD;
	}
}

void			ft_sub(t_field *field, t_process *process)
{
	unsigned	iter;
	int32_t		reg1;
	int32_t		reg2;
	int8_t		reg3;

	process->cur_cmd = SUB;
	if (cycles_waiting(process))
	{
		iter = 2;
		reg1 = get_first_param(field, process, &iter, BIG_DIR);
		reg2 = get_sec_param(field, process, &iter, BIG_DIR);
		reg3 = get_third_param(field, process, &iter, BIG_DIR);
		if (ft_is_nonvalid_addsub(field->map, process))
		{
			process->pos = (process->pos + iter) % MEM_SIZE;
			process->cur_cmd = FREE_CMD;
			return ;
		}
		init_regs(process, &reg1, &reg2);
		write_to_memory_4_bytes(process->registers[reg3 - 1], 0, reg1 - reg2);
		process->pos = (process->pos + iter) % MEM_SIZE;
		change_carry(process,
			read_from_memory_4_bytes(process->registers[reg3 - 1], 0));
		process->cur_cmd = FREE_CMD;
	}
}
