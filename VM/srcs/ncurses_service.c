/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_service.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:11:11 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 19:11:12 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			recreate(void)
{
	endwin();
	refresh();
	clear();
}

void			handle_speed(t_field *field, int key)
{
	if (key == KEY_UP)
		++(field->delay);
	else if (field->delay > 1)
		--(field->delay);
}

void			end_of_game(t_field *field)
{
	unsigned	tmp;
	unsigned	bi;
	unsigned	i;

	tmp = 0;
	bi = 0;
	i = 0;
	while (i < field->num_of_players)
		if (field->players[i++]->last_live_iter > tmp)
		{
			tmp = field->players[i - 1]->last_live_iter;
			bi = i - 1;
		}
	attron(DEFAULT_COLOR | A_BOLD);
	mvwprintw(stdscr, 50, BAR_BOARD, "Winner: %s", field->players[bi]->name);
	attroff(DEFAULT_COLOR | A_BOLD);
}

void			handle_key(t_field *field, int key)
{
	if (key == KEY_SPACE)
		SWITCH_PAUSE;
	else if (key == KEY_UP || key == KEY_DOWN)
		handle_speed(field, key);
	else if (key == KEY_RESIZE)
		recreate();
}
