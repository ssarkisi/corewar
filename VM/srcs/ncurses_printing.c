/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_printing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:33:49 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:33:49 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define DELTA_COLOR_CURSOR 6

void		print_box(void)
{
	int		x;
	int		y;

	attron(COLOR_PAIR(BOX_COLOR));
	y = 0;
	while (y < BOX_DOWN_BOARD)
	{
		x = 0;
		while (x < BOX_RIGHT_BOARD)
		{
			move(y, x);
			if (x == 0 || x == (BOX_RIGHT_BOARD - 1)\
			|| x == (BAR_BOARD - INDENT_BAR_BOARD))
				wprintw(stdscr, "|");
			move(y, x);
			if (y == 0 || y == (BOX_DOWN_BOARD - 1))
				wprintw(stdscr, "-");
			++x;
		}
		++y;
	}
	attroff(COLOR_PAIR(BOX_COLOR));
}

static void	print_info_player(t_field *field, unsigned num_of_player)
{
	int			termination_value;
	int			val;
	unsigned	pos;

	termination_value = 0;
	val = field->players[num_of_player]->number_of_player;
	while (val && (--termination_value))
		val /= 10;
	termination_value += 45;
	pos = 10 + num_of_player * 4;
	if (ft_strlen(field->players[num_of_player]->name) >\
	(unsigned)termination_value)
		field->players[num_of_player]->name[termination_value] = 0;
	mvwprintw(stdscr, pos, BAR_BOARD, "Player %d: %s",\
		field->players[num_of_player]->number_of_player,\
		field->players[num_of_player]->name);
	mvwprintw(stdscr, pos + 1, BAR_BOARD + 2,\
		"Last live:\t%u", field->players[num_of_player]->last_live_iter);
}

void		print_infobar(t_field *field)
{
	unsigned	iter;

	attron(DEFAULT_COLOR | A_BOLD);
	move(3, BAR_BOARD);
	PAUSE ? wprintw(stdscr, "PAUSE  ") : wprintw(stdscr, "RUNNING");
	mvwprintw(stdscr, 5, BAR_BOARD, "Cycle/sec:\t%u    ", field->delay);
	mvwprintw(stdscr, 6, BAR_BOARD, "Cycles:\t%u", field->cur_iter);
	mvwprintw(stdscr, 8, BAR_BOARD, "Processes:\t%u   ", field->num_of_proc);
	iter = 0;
	while (iter < field->num_of_players)
	{
		print_info_player(field, iter);
		++iter;
	}
	mvwprintw(stdscr, 27, BAR_BOARD,\
		"CYCLE TO DIE:\t%d      ", field->cycle_to_die);
	mvwprintw(stdscr, 29, BAR_BOARD,\
		"CYCLE DELTA:\t%d      ", CYCLE_DELTA);
	mvwprintw(stdscr, 31, BAR_BOARD,\
		"NBR LIVE:\t%d      ", NBR_LIVE);
	mvwprintw(stdscr, 33, BAR_BOARD,\
		"MAX CHECKS:\t%d      ", MAX_CHECKS);
	attroff(DEFAULT_COLOR | A_BOLD);
}

static void	print_cursor_or_byte(t_field *field, unsigned cursor_pos)
{
	unsigned	delta_cursor_color;
	_Bool		find;
	t_process	*process;

	find = FALSE;
	process = field->processes;
	while (process)
	{
		if (process->pos == cursor_pos)
		{
			find = TRUE;
			break ;
		}
		process = process->next;
	}
	if (find)
		delta_cursor_color = DELTA_COLOR_CURSOR;
	else
		delta_cursor_color = 0;
	attron(COLOR_PAIR(field->colors_bytes[cursor_pos] +\
		delta_cursor_color) | A_NORMAL);
	wprintw(stdscr, "%.2x", field->map[cursor_pos]);
	attroff(COLOR_PAIR(field->colors_bytes[cursor_pos] +\
		delta_cursor_color) | A_NORMAL);
}

void		print_bytes(t_field *field)
{
	unsigned	iter;
	int			x;
	int			y;

	x = 3;
	y = 2;
	iter = 0;
	while (iter < MEM_SIZE)
	{
		move(y, x);
		print_cursor_or_byte(field, iter);
		if (iter == 0 || (iter + 1) % SQRT_MEM_SIZE)
			x += 3;
		else
		{
			x = 3;
			y += 1;
		}
		++iter;
	}
}
