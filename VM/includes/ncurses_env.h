/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_env.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:59:10 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/15 16:00:07 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_NCURSES_ENV_H
# define COREWAR_NCURSES_ENV_H

# include <ncurses.h>
# include <stdlib.h>

# define WIN_WIDTH ...
# define WIN_HEIGHT ...

# define KEY_EXIT_COREWAR 113
# define KEY_SPACE 32
# define SQRT_MEM_SIZE 64

# define BAR_BOARD 202
# define INDENT_BAR_BOARD 5
# define BOX_RIGHT_BOARD 260
# define BOX_DOWN_BOARD (SQRT_MEM_SIZE + 4)

# define PAUSE (g_game_status & 1)
# define SWITCH_PAUSE (g_game_status ^= 1)

# define DEFAULT_COLOR 1
# define FIRST_PLAYER_COLOR 2
# define SECOND_PLAYER_COLOR 3
# define THIRD_PLAYER_COLOR 4
# define FOURTH_PLAYER_COLOR 5
# define BOX_COLOR 6
# define CURSOR_DEFAULT 7
# define CURSOR_GREEN 8
# define CURSOR_BLUE 9
# define CURSOR_RED 10
# define CURSOR_CYAN 11

_Bool		g_game_status;

void		print_box(void);
void		print_bytes(t_field *field);
void		print_infobar(t_field *field);

#endif
