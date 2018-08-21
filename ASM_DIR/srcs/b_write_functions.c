/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_write_functions.o                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssarkisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 16:29:04 by ssarkisi          #+#    #+#             */
/*   Updated: 2018/04/24 16:29:04 by ssarkisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		write_code(int fd, t_ol *ol)
{
	t_ol	*tmp;

	tmp = ol;
	while (tmp)
	{
		if (tmp->opcode != -1)
			write(fd, &tmp->opcode, 1);
		if (tmp->p_order > 0)
			write(fd, &tmp->p_order, 1);
		write(fd, &tmp->val1, get_arg_size(tmp, 1));
		if (tmp->argn > 1)
			write(fd, &tmp->val2, get_arg_size(tmp, 2));
		if (tmp->argn > 2)
			write(fd, &tmp->val3, get_arg_size(tmp, 3));
		tmp = tmp->next;
	}
}

void		write_code_size(int fd, int size)
{
	size = REVERSE_4_BYTES(size);
	write(fd, &size, 4);
}

void		write_magic(int fd)
{
	int		magic;

	magic = REVERSE_4_BYTES(COREWAR_EXEC_MAGIC);
	write(fd, &magic, 4);
}

void		write_name(int fd, char *name)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (name[i] != '\0')
	{
		write(fd, &name[i], 1);
		i++;
	}
	while (i < PROG_NAME_LENGTH)
	{
		write(fd, &n, 1);
		i++;
	}
}

void		write_comment(int fd, char *comment)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (comment[i] != '\0')
	{
		write(fd, &comment[i], 1);
		i++;
	}
	while (i < COMMENT_LENGTH)
	{
		write(fd, &n, 1);
		i++;
	}
}
