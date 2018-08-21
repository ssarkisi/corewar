/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_write.o                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssarkisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 17:51:33 by ssarkisi          #+#    #+#             */
/*   Updated: 2018/04/22 17:51:35 by ssarkisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		write_null(int fd)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (i < 4)
	{
		write(fd, &n, 1);
		i++;
	}
}

void		write_to_file(t_ol *ol, char *name, char *comment)
{
	int			fd;

	if (CHECK_BOT_SIZE == 1 && get_total_code_size(ol) > CHAMP_MAX_SIZE)
	{
		free_all(ol, &name, &comment);
		ft_putstr("ERROR: Too large bot size. The max allowed size is ");
		ft_putnbr(CHAMP_MAX_SIZE);
		ft_putstr(" bytes\n");
		exit(0);
	}
	fd = open(g_bin_file_name, O_WRONLY | O_CREAT | O_TRUNC,
			S_IREAD | S_IWRITE);
	write_magic(fd);
	write_name(fd, name);
	write_null(fd);
	write_code_size(fd, get_total_code_size(ol));
	write_comment(fd, comment);
	write_null(fd);
	write_code(fd, ol);
	write(1, "Writing output program to ", 26);
	ft_putstr(g_bin_file_name);
	write(1, "\n", 1);
	free_all(g_list->first, &name, &comment);
	close(fd);
}
