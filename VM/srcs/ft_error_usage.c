/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_usage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:32:56 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:32:56 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "corewar.h"

void	free_mem(t_field *field)
{
	t_process	*process;
	t_process	*tmp;
	unsigned	iter;

	g_game ? free(g_game) : 0;
	iter = 0;
	while (field && iter < field->num_of_players)
	{
		free(field->players[iter]->name);
		free(field->players[iter]->comment);
		free(field->players[iter++]);
	}
	field && field->players ? free(field->players) : 0;
	process = field ? field->processes : NULL;
	while (process)
	{
		tmp = process;
		process = process->next;
		free(tmp);
	}
	field ? free(field) : 0;
}

void	ft_error(char *err, t_field *field, void (free_mem)(t_field *field))
{
	if (free_mem)
		free_mem(field);
	write(1, err, ft_strlen(err));
	exit(1);
}

void	print_usage(void)
{
	write(1, "\a", 1);
	write(1, "Usage: ./corewar [-ncr | -dump nbr_cycles]"
			"[[-n number] champion1.cor] ...\n"
			"-------TEXT OUTPUT MODE-------\n"
			"    -dump N\t: Dumps memory after N cycles then exits\n"
			"    -n N\t: Sets the number of the next player\n"
			"------------------------------\n"
			"------NCURSES OUTPUT MODE-----\n"
			"    -ncr\t: Ncurses output mode\n"
			"------------------------------\n", 329);
}
