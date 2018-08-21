/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:33:15 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:33:16 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int32_t				get_first_param(t_field *field, t_process *process,\
										unsigned *iter, _Bool dir_mod)
{
	uint8_t		codage_octal;
	int32_t		val;

	val = 0;
	codage_octal = field->map[(process->pos + 1) % MEM_SIZE];
	if (IS_T_DIR_FIRST(codage_octal))
	{
		if (dir_mod && (*iter += 4))
			val = read_from_memory_4_bytes(field->map,\
				(process->pos + *iter - 4) % MEM_SIZE);
		else if ((*iter += 2))
			val = read_from_memory_2_bytes(field->map,\
				(process->pos + *iter - 2) % MEM_SIZE);
	}
	else if (IS_T_IND_FIRST(codage_octal) && (*iter += 2))
		val = read_from_memory_2_bytes(field->map,\
			(process->pos + *iter - 2) % MEM_SIZE);
	else if (IS_T_REG_FIRST(codage_octal) && (*iter += 1))
		val = field->map[(process->pos + *iter - 1) % MEM_SIZE];
	return (val);
}

int32_t				get_sec_param(t_field *field, t_process *process,\
										unsigned *iter, _Bool dir_mod)
{
	uint8_t		codage_octal;
	int32_t		val;

	val = 0;
	codage_octal = field->map[(process->pos + 1) % MEM_SIZE];
	if (IS_T_DIR_SECOND(codage_octal))
	{
		if (dir_mod && (*iter += 4))
			val = read_from_memory_4_bytes(field->map,\
				(process->pos + *iter - 4) % MEM_SIZE);
		else if ((*iter += 2))
			val = read_from_memory_2_bytes(field->map,\
				(process->pos + *iter - 2) % MEM_SIZE);
	}
	else if (IS_T_IND_SECOND(codage_octal) && (*iter += 2))
		val = read_from_memory_2_bytes(field->map,\
			(process->pos + *iter - 2) % MEM_SIZE);
	else if (IS_T_REG_SECOND(codage_octal) && (*iter += 1))
		val = field->map[(process->pos + *iter - 1) % MEM_SIZE];
	return (val);
}

int32_t				get_third_param(t_field *field, t_process *process,\
										unsigned *iter, _Bool dir_mod)
{
	uint8_t		codage_octal;
	int32_t		val;

	val = 0;
	codage_octal = field->map[(process->pos + 1) % MEM_SIZE];
	if (IS_T_DIR_THIRD(codage_octal))
	{
		if (dir_mod && (*iter += 4))
			val = read_from_memory_4_bytes(field->map,\
				(process->pos + *iter - 4) % MEM_SIZE);
		else if ((*iter += 2))
			val = read_from_memory_2_bytes(field->map,\
				(process->pos + *iter - 2) % MEM_SIZE);
	}
	else if (IS_T_IND_THIRD(codage_octal) && (*iter += 2))
		val = read_from_memory_2_bytes(field->map,\
			(process->pos + *iter - 2) % MEM_SIZE);
	else if (IS_T_REG_THIRD(codage_octal) && (*iter += 1))
		val = field->map[(process->pos + *iter - 1) % MEM_SIZE];
	return (val);
}
