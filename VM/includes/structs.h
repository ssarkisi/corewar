/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:01:49 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/15 16:03:57 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdint.h>
# include "op.h"
# include "corewar.h"

/*
** Game Mode
*/

typedef enum			e_gamemode
{
	DEFAULT,
	VISUAL,
	DUMP
}						t_gamemode;

/*
** game
*/

typedef struct			s_game
{
	t_gamemode			mode;
	int					value;
	int					nums_of_players[MAX_PLAYERS];
}						t_game;

/*
** player
*/

typedef struct			s_player
{
	int32_t				number_of_player;
	char				*name;
	char				*comment;
	unsigned			last_live_iter;
}						t_player;

/*
** processes
*/

typedef struct			s_process
{
	int8_t				registers[REG_NUMBER][REG_SIZE];
	unsigned			pos;
	unsigned			cycles_waiting;
	uint8_t				color;
	_Bool				carry;
	struct s_process	*next;
	unsigned			num_live_in_cur_period;
	unsigned			nbr_live_said;
	int8_t				cur_cmd;
}						t_process;

/*
** field
*/

typedef struct			s_field
{
	int8_t				colors_bytes[MEM_SIZE];
	uint8_t				map[MEM_SIZE];
	t_process			*processes;
	unsigned			num_of_proc;
	t_player			**players;
	unsigned			num_of_players;
	unsigned			cur_iter;
	unsigned			end_of_last_period;
	int					cycle_to_die;
	unsigned			delay;
	unsigned			nbr_live;
	unsigned			num_check;
}						t_field;

#endif
