/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:33:20 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:33:21 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_tuner(t_field *field)
{
	if (g_game->mode == VISUAL)
		run_visual(field);
	else if (g_game->mode == DUMP)
		run_dump(field, g_game->value);
	else if (g_game->mode == DEFAULT)
		run_default(field);
	free_mem(field);
}

int			main(int argc, char **argv)
{
	t_field		*field;

	if (argc == 1)
	{
		print_usage();
		return (0);
	}
	if (!(field = generate_field()))
		ft_error("Something went wrong\n", NULL, NULL);
	if (!(g_game = generate_game_info()))
		ft_error("Something went wrong\n", field, free_mem);
	if (!(ft_read_commands(argc, argv, field)))
		ft_error("Something went wrong\n", field, free_mem);
	ft_tuner(field);
	return (0);
}
