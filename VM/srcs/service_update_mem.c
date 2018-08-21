/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_update_mem.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:34:31 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:34:31 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

_Bool			cycles_waiting(t_process *process)
{
	static const unsigned	cycles_wait[16] =\
	{10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};

	++(process->cycles_waiting);
	if (process->cycles_waiting < cycles_wait[process->cur_cmd - 1])
		return (FALSE);
	else
	{
		process->cycles_waiting = 0;
		return (TRUE);
	}
}

int32_t			read_from_memory_4_bytes(void *mem, int32_t index)
{
	int32_t		val;

	val = 0;
	val |= (((int8_t*)mem)[index % MEM_SIZE] & 0xff);
	val <<= 8;
	val |= (((int8_t*)mem)[(index + 1) % MEM_SIZE] & 0xff);
	val <<= 8;
	val |= (((int8_t*)mem)[(index + 2) % MEM_SIZE] & 0xff);
	val <<= 8;
	val |= (((int8_t*)mem)[(index + 3) % MEM_SIZE] & 0xff);
	return (val);
}

int16_t			read_from_memory_2_bytes(void *mem, int32_t index)
{
	int16_t		val;

	val = 0;
	val |= (((int8_t*)mem)[index % MEM_SIZE] & 0xff);
	val <<= 8;
	val |= (((int8_t*)mem)[(index + 1) % MEM_SIZE] & 0xff);
	return (val);
}

void			write_to_memory_4_bytes(void *mem, int32_t index, int32_t val)
{
	((int8_t*)mem)[(index + 3) % MEM_SIZE] = (int8_t)(val & 0xFF);
	((int8_t*)mem)[(index + 2) % MEM_SIZE] = (int8_t)((val >> 8) & 0xFF);
	((int8_t*)mem)[(index + 1) % MEM_SIZE] = (int8_t)((val >> 16) & 0xFF);
	((int8_t*)mem)[index % MEM_SIZE] = (int8_t)((val >> 24) & 0xFF);
}

void			write_color(t_field *field, int32_t index, uint8_t color)
{
	unsigned	iter;

	iter = 0;
	while (iter < REG_SIZE)
	{
		field->colors_bytes[index++ % MEM_SIZE] = color;
		++iter;
	}
}
