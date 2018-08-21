/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:34:23 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:34:23 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		dell_process(t_field *field, t_process **process, t_process **prev)
{
	if (field->processes == *process)
	{
		field->processes = field->processes->next;
		free(*process);
		*process = field->processes;
		*prev = field->processes;
	}
	else
	{
		(*prev)->next = (*process)->next;
		free(*process);
		*process = (*prev)->next;
	}
}

void		copy_process_to_dir(t_process *proc, unsigned new_pos, t_field *f)
{
	t_process	*new_proc;
	unsigned	iter;

	new_proc = generate_process(new_pos);
	new_proc->next = f->processes;
	f->processes = new_proc;
	new_proc->cycles_waiting = 0;
	new_proc->num_live_in_cur_period = proc->num_live_in_cur_period;
	new_proc->color = proc->color;
	new_proc->carry = proc->carry;
	iter = 0;
	while (iter < REG_NUMBER)
	{
		write_to_memory_4_bytes(new_proc->registers[iter], 0,\
			read_from_memory_4_bytes(proc->registers[iter], 0));
		++iter;
	}
	++(f->num_of_proc);
}
