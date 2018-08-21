/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:34:05 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:34:06 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		add_player(t_field *field, char *cor_file)
{
	if (!(field->players))
		field->players = (t_player**)ft_memalloc(sizeof(t_player*));
	else
		field->players = (t_player**)ft_realloc_modf(field->players,
							sizeof(t_player*) * (field->num_of_players + 1),
							sizeof(t_player*) * field->num_of_players);
	field->players[field->num_of_players] = generate_player(
							ft_strsub(cor_file, START_NAME, PROG_NAME_LENGTH),
							ft_strsub(cor_file, START_COMM, COMMENT_LENGTH));
	field->players[field->num_of_players]->number_of_player =
							g_game->nums_of_players[field->num_of_players];
	++(field->num_of_players);
}

static void		add_process(t_field *field, int num_all_players)
{
	t_process	*proc_tmp;
	unsigned	default_pos;

	default_pos = MEM_SIZE / num_all_players * field->num_of_players;
	proc_tmp = generate_process(default_pos);
	proc_tmp->next = field->processes;
	field->processes = proc_tmp;
	proc_tmp->color = field->num_of_players + 2;
	write_to_memory_4_bytes(proc_tmp->registers[0], 0,
						g_game->nums_of_players[field->num_of_players]);
	++(field->num_of_proc);
}

static void		write_bytes(t_field *field, char const *cor_file,
							int num_all_players)
{
	t_process	*tmp_proc;
	unsigned	end_index_of_exec;
	unsigned	iter;
	unsigned	i;
	uint8_t		cur_color;

	tmp_proc = field->processes;
	cur_color = tmp_proc->color;
	i = REVERSE_4_BYTES(*(unsigned*)(&(cor_file[PROG_NAME_LENGTH + 8])));
	end_index_of_exec = START_CODE + i;
	iter = START_CODE;
	i = MEM_SIZE / num_all_players * field->num_of_players;
	while (iter < end_index_of_exec)
	{
		field->map[i] = cor_file[iter];
		field->colors_bytes[i] = cur_color;
		++i;
		++iter;
	}
}

static int		check_num_players(t_field *field, int argc, char **argv)
{
	int		num_of_players;

	if ((num_of_players = get_num_of_players(argc, argv)) > MAX_PLAYERS ||
		(num_of_players = get_num_of_players(argc, argv)) < 1)
		ft_error("Error\n", field, free_mem);
	return (num_of_players);
}

_Bool			ft_read_commands(int argc, char **argv, t_field *field)
{
	int			num_of_players;
	unsigned	iter;
	char		*cor_file;

	num_of_players = check_num_players(field, argc, argv);
	iter = 1;
	while (argv[iter])
	{
		if (*(argv[iter]) == '-' && handle_param(field, argv, &iter))
			continue ;
		else if (!(cor_file = read_from_file(argv[iter])))
			ft_error("Invalid file\n", field, free_mem);
		if (read_from_memory_4_bytes(cor_file, 0) !=
				(uint32_t)COREWAR_EXEC_MAGIC)
		{
			free(cor_file);
			ft_error("Incorrect magic number\n", field, free_mem);
		}
		add_process(field, num_of_players);
		write_bytes(field, cor_file, num_of_players);
		add_player(field, cor_file);
		free(cor_file);
		++iter;
	}
	return (TRUE);
}
