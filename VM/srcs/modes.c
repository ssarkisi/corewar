/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:33:30 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:33:31 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		print_info(t_field *field)
{
	char		*tmp;
	unsigned	i;

	i = 0;
	while (i < field->num_of_players)
	{
		write(1, "Player ", 7);
		tmp = ft_itoa(field->players[i]->number_of_player);
		write(1, tmp, ft_strlen(tmp));
		free(tmp);
		write(1, ": ", 2);
		write(1, field->players[i]->name, ft_strlen(field->players[i]->name));
		write(1, " (", 2);
		write(1, field->players[i]->comment,
			ft_strlen(field->players[i]->comment));
		write(1, ")\n", 2);
		++i;
	}
}

static void		print_winner(t_field *field)
{
	char		*tmp;
	unsigned	biter;
	unsigned	bi;
	unsigned	i;

	i = 0;
	bi = 0;
	biter = 0;
	while (i < field->num_of_players)
		if (field->players[i++]->last_live_iter > biter)
		{
			biter = field->players[i - 1]->last_live_iter;
			bi = i - 1;
		}
	write(1, "Player ", 7);
	tmp = ft_itoa(field->players[bi]->number_of_player);
	write(1, tmp, ft_strlen(tmp));
	free(tmp);
	write(1, " (", 2);
	write(1, field->players[bi]->name, ft_strlen(field->players[bi]->name));
	write(1, ") won\n", 6);
}

void			run_default(t_field *field)
{
	print_info(field);
	while (ft_update_mem(field))
		;
	print_winner(field);
}

void			run_dump(t_field *field, int value)
{
	char	*num_hex;
	int		i;

	i = 0;
	while (i < value)
	{
		ft_update_mem(field);
		i++;
	}
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i && !(i % 64))
			write(1, "\n", 1);
		else if (i)
			write(1, " ", 1);
		num_hex = ft_itoa_base(field->map[i], 16);
		if (*(num_hex + 1) == 0)
			write(1, "0", 1);
		write(1, num_hex, ft_strlen(num_hex));
		free(num_hex);
		++i;
	}
	write(1, "\n", 1);
}
