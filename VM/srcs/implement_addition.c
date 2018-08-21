/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_addition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 21:10:36 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 21:10:37 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			unknown_command(t_field *field, t_process *process)
{
	(void)field;
	++(process->pos);
	process->pos %= MEM_SIZE;
}

void			print_log_live(t_field *field, unsigned index_player)
{
	char	*tmp;

	write(1, "A procces show that player ", 27);
	tmp = ft_itoa(field->players[index_player]->number_of_player);
	write(1, tmp, ft_strlen(tmp));
	free(tmp);
	write(1, " (", 2);
	write(1, field->players[index_player]->name,\
		ft_strlen(field->players[index_player]->name));
	write(1, ") is alive\n", 11);
}

void			ft_aff(t_field *field, t_process *process)
{
	unsigned	iter;
	int32_t		val;
	int8_t		reg;

	process->cur_cmd = AFF;
	if (cycles_waiting(process))
	{
		iter = 2;
		reg = get_first_param(field, process, &iter, BIG_DIR);
		if (ft_is_nonvalid_aff(field->map, process))
		{
			process->pos = (process->pos + iter) % MEM_SIZE;
			process->cur_cmd = FREE_CMD;
			return ;
		}
		val = read_from_memory_4_bytes(process->registers[reg - 1], 0) % 256;
		if (ft_isprint(val))
			write(1, &val, 1);
		process->pos = (process->pos + iter) % MEM_SIZE;
		process->cur_cmd = FREE_CMD;
	}
}
