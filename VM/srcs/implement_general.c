/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_general.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:32:28 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:32:29 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** General commands
*/

void					ft_live(t_field *field, t_process *process)
{
	unsigned	iter;

	process->cur_cmd = LIVE;
	if (cycles_waiting(process))
	{
		++(process->num_live_in_cur_period);
		++(process->nbr_live_said);
		iter = 0;
		while (iter < field->num_of_players)
		{
			if (read_from_memory_4_bytes(field->map, process->pos + 1) ==\
				field->players[iter]->number_of_player)
			{
				field->players[iter]->last_live_iter = field->cur_iter;
				if (g_game->mode == DEFAULT && LOG_LIVE)
					print_log_live(field, iter);
			}
			++iter;
		}
		process->pos = (process->pos + 5) % MEM_SIZE;
		process->cur_cmd = FREE_CMD;
	}
}

void					ft_zjump(t_field *field, t_process *process)
{
	int16_t		dir;

	process->cur_cmd = ZJMP;
	if (cycles_waiting(process))
	{
		if (process->carry == TRUE)
		{
			dir = read_from_memory_2_bytes(field->map, process->pos + 1);
			dir %= IDX_MOD;
			if (dir < 0)
				dir = (MEM_SIZE + (dir + process->pos)) % MEM_SIZE;
			else
				dir = (process->pos + dir) % MEM_SIZE;
			process->pos = dir;
		}
		else
			process->pos = (process->pos + 3) % MEM_SIZE;
		process->cur_cmd = FREE_CMD;
	}
}

void					ft_fork(t_field *field, t_process *process)
{
	int16_t		dir;

	process->cur_cmd = FORK;
	if (cycles_waiting(process))
	{
		dir = read_from_memory_2_bytes(field->map, process->pos + 1) % IDX_MOD;
		if (dir < 0)
			dir = (MEM_SIZE + (dir + process->pos));
		else
			dir += process->pos;
		dir %= MEM_SIZE;
		copy_process_to_dir(process, dir, field);
		process->pos = (process->pos + 3) % MEM_SIZE;
		process->cur_cmd = FREE_CMD;
	}
}

void					ft_lfork(t_field *field, t_process *process)
{
	int16_t		dir;

	process->cur_cmd = LFORK;
	if (cycles_waiting(process))
	{
		dir = read_from_memory_2_bytes(field->map, process->pos + 1) % MEM_SIZE;
		if (dir < 0)
			dir = (MEM_SIZE + (dir + process->pos));
		else
			dir += process->pos;
		dir %= MEM_SIZE;
		copy_process_to_dir(process, dir, field);
		process->pos = (process->pos + 3) % MEM_SIZE;
		process->cur_cmd = FREE_CMD;
	}
}
