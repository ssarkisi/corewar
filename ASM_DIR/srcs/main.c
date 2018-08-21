/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.o                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssarkisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 12:20:39 by ssarkisi          #+#    #+#             */
/*   Updated: 2018/04/20 12:20:41 by ssarkisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		asmembler(t_ol *ol, char **all, char **tmp)
{
	char		*name;
	char		*com;

	check_labels(ol->first, all);
	name = ft_strdup(tmp[0]);
	com = ft_strdup(tmp[1]);
	free_str_arr(tmp);
	set_code_param(ol);
	set_arg_val(ol);
	write_to_file(ol, name, com);
}

void		read_all(int fd)
{
	char		*line;
	int			rows;
	char		**all;

	g_list = NULL;
	if (fd < 1)
	{
		write(1, "ERROR: not valid file\n", 22);
		ft_strdel(&g_bin_file_name);
		exit(0);
	}
	rows = 1;
	all = malloc(sizeof(char*) * rows);
	while (get_next_line(fd, &line))
	{
		all[rows - 1] = ft_strdup(line);
		rows++;
		all = realloc(all, sizeof(char*) * rows);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	all[rows - 1] = NULL;
	validate_all(all, rows, 0, 0);
	free_all_ar(&all);
}

void		set_new_file_name(char *av)
{
	int		i;
	int		len;
	char	*file_name;

	if (g_bin_file_name)
		free(g_bin_file_name);
	i = 0;
	len = ft_strlen(av);
	file_name = ft_strnew(len + 2);
	while (i < len)
	{
		file_name[i] = av[i];
		i++;
	}
	file_name[i - 1] = 'c';
	file_name[i] = 'o';
	file_name[i + 1] = 'r';
	file_name[i + 2] = '\0';
	g_bin_file_name = file_name;
}

int			main(int ac, char **av)
{
	int		fd;
	int		i;

	i = 1;
	g_bin_file_name = NULL;
	if (ac < 2)
		return (0);
	if (ac == 4 && ft_strcmp(av[1], "-o") == 0)
	{
		g_bin_file_name = ft_strdup(av[2]);
		fd = open(av[3], O_RDWR);
		read_all(fd);
		close(fd);
	}
	else
		while (i < ac)
		{
			g_bin_file_name = NULL;
			set_new_file_name(av[i]);
			fd = open(av[i], O_RDWR);
			read_all(fd);
			i++;
			close(fd);
		}
	return (0);
}
