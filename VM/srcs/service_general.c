/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_general.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:34:14 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:34:15 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char			*read_from_file(char *filename)
{
	FILE	*file;
	ssize_t	clen;
	char	*buffer;

	if (!(file = fopen(filename, "r")))
		return (NULL);
	clen = SIZE_OF_ALL_FILE;
	if (!(buffer = (char*)ft_memalloc(clen * sizeof(char))))
		return (NULL);
	clen = fread(buffer, sizeof(char), SIZE_OF_ALL_FILE, file) - START_CODE;
	if (clen != REVERSE_4_BYTES(*(int32_t*)&buffer[START_COMM - 4]) ||
			!feof(file))
		return (NULL);
	return (buffer);
}

int32_t			get_handled_index(t_process *process, int32_t index,
									int32_t idx_mode)
{
	int32_t		res;

	idx_mode ? (index %= idx_mode) : 0;
	if (index < 0)
		res = (MEM_SIZE + (index + process->pos)) % MEM_SIZE;
	else
		res = (index + process->pos) % MEM_SIZE;
	return (res);
}

void			change_carry(t_process *process, int32_t val)
{
	if (val == 0)
		process->carry = TRUE;
	else
		process->carry = FALSE;
}
