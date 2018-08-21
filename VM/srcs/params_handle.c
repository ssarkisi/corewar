/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:33:57 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:33:57 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static _Bool	check_colision_num(int *nums, int ind_board, int num)
{
	int		i;

	i = 0;
	while (i < ind_board)
		if (nums[i++] == num)
			return (TRUE);
	return (FALSE);
}

static void		add_num_player(t_field *field, int num)
{
	int		i;

	if (check_colision_num(g_game->nums_of_players, field->num_of_players, num))
		ft_error("Invalid param\n", field, free_mem);
	g_game->nums_of_players[field->num_of_players] = num;
	i = field->num_of_players + 1;
	while (i < MAX_PLAYERS)
	{
		while (check_colision_num(g_game->nums_of_players, i, num))
			++num;
		g_game->nums_of_players[i] = num;
		++i;
	}
}

_Bool			handle_param(t_field *field, char **argv, unsigned *index)
{
	if (!ft_strcmp(argv[*index], "-dump"))
	{
		if (*(argv[*index + 1]) == '-' || !ft_isint(argv[*index + 1]))
			ft_error("Invalid param\n", field, free_mem);
		g_game->mode = DUMP;
		g_game->value = ft_atoi(argv[*index + 1]);
		*index += 2;
	}
	else if (!ft_strcmp(argv[*index], "-n"))
	{
		if (!ft_isint(argv[*index + 1]))
			ft_error("Invalid param\n", field, free_mem);
		add_num_player(field, ft_atoi(argv[*index + 1]));
		*index += 2;
	}
	else if (!ft_strcmp(argv[*index], "-ncr"))
	{
		g_game->mode = VISUAL;
		*index += 1;
	}
	else
		ft_error("Invalid param\n", field, free_mem);
	return (TRUE);
}

int				get_num_of_players(int argc, char **argv)
{
	int		minus;
	int		i;

	minus = 1;
	i = 1;
	while (argv[i])
	{
		if (*(argv[i]) == '-' && !ft_isnumber(argv[i]))
		{
			if (!ft_strcmp(argv[i], "-ncr"))
				++minus;
			else
				minus += 2;
		}
		++i;
	}
	return (argc - minus);
}
