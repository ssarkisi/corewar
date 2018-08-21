/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:34:37 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:34:38 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define END_OF_GAME FALSE

typedef void	(*t_command)(t_field *field, t_process *process);

t_command			search_command(int8_t byte)
{
	static const t_command	functions[16] = {ft_live, ft_ld, ft_st, ft_add,
											ft_sub, ft_and, ft_or, ft_xor,
											ft_zjump, ft_ldi, ft_sti,
											ft_fork, ft_lld, ft_lldi,
											ft_lfork, ft_aff};

	if (byte >= 0x01 && byte <= 0x10)
		return (functions[byte - 1]);
	else
		return (unknown_command);
}

static _Bool		ft_handle_live_from_proc(t_field *field,\
								t_process **process, t_process **prev)
{
	if ((*process)->num_live_in_cur_period)
	{
		field->nbr_live += (*process)->nbr_live_said;
		(*process)->num_live_in_cur_period = 0;
		(*process)->nbr_live_said = 0;
		return (FALSE);
	}
	else
	{
		dell_process(field, process, prev);
		--(field->num_of_proc);
		return (TRUE);
	}
}

static void			ft_handle_nbr_live(t_field *field)
{
	if (field->nbr_live >= NBR_LIVE)
	{
		field->cycle_to_die -= CYCLE_DELTA;
		field->num_check = 0;
	}
	else if (field->num_check >= MAX_CHECKS)
	{
		field->cycle_to_die -= CYCLE_DELTA;
		field->num_check = 0;
	}
	else
		++(field->num_check);
	field->nbr_live = 0;
	field->end_of_last_period = field->cur_iter;
}

_Bool				ft_update_mem(t_field *field)
{
	int8_t		cmd_byte;
	t_process	*process;
	t_process	*prev;

	if (!(field->processes) || field->cycle_to_die <= 0)
		return (END_OF_GAME);
	++(field->cur_iter);
	process = field->processes;
	prev = field->processes;
	while (process)
	{
		if (field->cur_iter ==\
				(field->end_of_last_period + field->cycle_to_die) &&\
				ft_handle_live_from_proc(field, &process, &prev))
			continue ;
		cmd_byte = process->cur_cmd != FREE_CMD ?\
						process->cur_cmd : field->map[process->pos];
		search_command(cmd_byte)(field, process);
		if (prev != process)
			prev = prev->next;
		process = process->next;
	}
	if (field->cur_iter == (field->end_of_last_period + field->cycle_to_die))
		ft_handle_nbr_live(field);
	return (TRUE);
}
