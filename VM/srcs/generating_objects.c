/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generating_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:33:03 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:33:04 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#ifndef NULL_BYTE
# define NULL_BYTE 0
#endif

t_game		*generate_game_info(void)
{
	unsigned	iter;
	t_game		*new_game;

	if (!(new_game = (t_game*)ft_memalloc(sizeof(t_game))))
		return (NULL);
	new_game->mode = DEFAULT;
	new_game->value = 0;
	iter = 0;
	while (iter < MAX_PLAYERS)
	{
		new_game->nums_of_players[iter] = -(iter + 1);
		++iter;
	}
	return (new_game);
}

t_field		*generate_field(void)
{
	t_field		*new_field;

	if (!(new_field = (t_field*)ft_memalloc(sizeof(t_field))))
		return (NULL);
	ft_memset(new_field->map, NULL_BYTE, MEM_SIZE);
	ft_memset(new_field->colors_bytes, DEFAULT_COLOR, MEM_SIZE);
	new_field->cur_iter = 0;
	new_field->end_of_last_period = 0;
	new_field->cycle_to_die = CYCLE_TO_DIE;
	new_field->num_check = 0;
	new_field->nbr_live = 0;
	new_field->processes = 0;
	new_field->players = 0;
	new_field->num_of_proc = 0;
	new_field->num_of_players = 0;
	new_field->delay = 50;
	return (new_field);
}

t_process	*generate_process(unsigned pos)
{
	t_process	*new_proc;
	size_t		iter;

	if (!(new_proc = (t_process*)ft_memalloc(sizeof(t_process))))
		return (NULL);
	iter = 0;
	while (iter < REG_NUMBER)
		ft_memset(new_proc->registers[iter++], NULL_BYTE, REG_SIZE);
	new_proc->pos = pos;
	new_proc->cycles_waiting = 0;
	new_proc->cur_cmd = FREE_CMD;
	new_proc->color = DEFAULT_COLOR;
	new_proc->carry = FALSE;
	new_proc->next = 0;
	new_proc->num_live_in_cur_period = 0;
	new_proc->nbr_live_said = 0;
	return (new_proc);
}

t_player	*generate_player(char *name, char *comment)
{
	t_player	*new_player;

	if (!(new_player = (t_player*)ft_memalloc(sizeof(t_player))))
		return (NULL);
	new_player->name = name;
	new_player->comment = comment;
	new_player->last_live_iter = 0;
	new_player->number_of_player = -1;
	return (new_player);
}
