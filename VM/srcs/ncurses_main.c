/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:33:39 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:33:40 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "corewar.h"

static void		init_win(void)
{
	initscr();
	noecho();
	cbreak();
	start_color();
	init_color(COLOR_WHITE, 255, 255, 255);
	init_pair(DEFAULT_COLOR, COLOR_WHITE, COLOR_BLACK);
	init_pair(BOX_COLOR, COLOR_WHITE, COLOR_WHITE);
	init_pair(FIRST_PLAYER_COLOR, COLOR_GREEN, COLOR_BLACK);
	init_pair(SECOND_PLAYER_COLOR, COLOR_BLUE, COLOR_BLACK);
	init_pair(THIRD_PLAYER_COLOR, COLOR_RED, COLOR_BLACK);
	init_pair(FOURTH_PLAYER_COLOR, COLOR_CYAN, COLOR_BLACK);
	init_pair(CURSOR_DEFAULT, COLOR_BLACK, COLOR_WHITE);
	init_pair(CURSOR_GREEN, COLOR_BLACK, COLOR_GREEN);
	init_pair(CURSOR_BLUE, COLOR_BLACK, COLOR_BLUE);
	init_pair(CURSOR_RED, COLOR_BLACK, COLOR_RED);
	init_pair(CURSOR_CYAN, COLOR_BLACK, COLOR_CYAN);
	curs_set(0);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
}

static void		inf_loop(t_field *field)
{
	int64_t		deltatime;
	clock_t		start;
	clock_t		end;
	int			key;

	SWITCH_PAUSE;
	while ((key = getch()) != KEY_EXIT_COREWAR)
	{
		print_box();
		start = clock();
		handle_key(field, key);
		print_infobar(field);
		print_bytes(field);
		if (PAUSE && key != KEY_RIGHT)
			continue ;
		if (!(ft_update_mem(field)))
			end_of_game(field);
		refresh();
		end = clock();
		deltatime = 1000000 / field->delay - (end - start);
		usleep(deltatime >= 0 ? deltatime : 0);
	}
}

void			run_visual(t_field *field)
{
	init_win();
	inf_loop(field);
	endwin();
}
