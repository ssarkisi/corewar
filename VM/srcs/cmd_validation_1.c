/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:32:44 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 12:32:44 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

_Bool			ft_is_nonvalid_ld(uint8_t *map, t_process *process)
{
	unsigned	iter;
	uint8_t		codage_octal;

	iter = 2;
	codage_octal = map[(process->pos + 1) % MEM_SIZE];
	IS_T_DIR_FIRST(codage_octal) ? (iter += 4) : 0;
	IS_T_IND_FIRST(codage_octal) ? (iter += 2) : 0;
	if (!map[(process->pos + iter) % MEM_SIZE] ||
			map[(process->pos + iter) % MEM_SIZE] > 16)
		return (TRUE);
	if ((!IS_T_DIR_FIRST(codage_octal) && !IS_T_IND_FIRST(codage_octal)) ||
			!IS_T_REG_SECOND(codage_octal))
		return (TRUE);
	return (FALSE);
}

_Bool			ft_is_nonvalid_ldi(uint8_t *map, t_process *process)
{
	unsigned	iter;
	uint8_t		codage_octal;

	iter = 2;
	codage_octal = map[(process->pos + 1) % MEM_SIZE];
	if (IS_T_REG_FIRST(codage_octal) &&
			(!map[(process->pos + iter) % MEM_SIZE] ||
			map[(process->pos + iter) % MEM_SIZE] > 16))
		return (TRUE);
	!IS_T_REG_FIRST(codage_octal) ? (iter += 2) : 0;
	IS_T_REG_FIRST(codage_octal) ? (iter += 1) : 0;
	if (IS_T_REG_SECOND(codage_octal) &&
			(!map[(process->pos + iter) % MEM_SIZE] ||
			map[(process->pos + iter) % MEM_SIZE] > 16))
		return (TRUE);
	!IS_T_REG_SECOND(codage_octal) ? (iter += 2) : 0;
	IS_T_REG_SECOND(codage_octal) ? (iter += 1) : 0;
	if (!map[(process->pos + iter) % MEM_SIZE] ||
			map[(process->pos + iter) % MEM_SIZE] > 16)
		return (TRUE);
	if ((codage_octal & 0xc0) == 0x0 || (!IS_T_REG_SECOND(codage_octal) &&
			!IS_T_DIR_SECOND(codage_octal))
			|| !IS_T_REG_THIRD(codage_octal))
		return (TRUE);
	return (FALSE);
}

_Bool			ft_is_nonvalid_st(uint8_t *map, t_process *process)
{
	unsigned	iter;
	uint8_t		codage_octal;

	iter = 2;
	codage_octal = map[(process->pos + 1) % MEM_SIZE];
	if (!map[(process->pos + iter) % MEM_SIZE] ||
			map[(process->pos + iter) % MEM_SIZE] > 16)
		return (TRUE);
	IS_T_REG_FIRST(codage_octal) ? (iter += 1) : 0;
	if (IS_T_REG_SECOND(codage_octal) &&
			(!map[(process->pos + iter) % MEM_SIZE] ||
			map[(process->pos + iter) % MEM_SIZE] > 16))
		return (TRUE);
	if (!IS_T_REG_FIRST(codage_octal) || (!IS_T_REG_SECOND(codage_octal) &&
			!IS_T_IND_SECOND(codage_octal)))
		return (TRUE);
	return (FALSE);
}

_Bool			ft_is_nonvalid_sti(uint8_t *map, t_process *process)
{
	unsigned	iter;
	uint8_t		codage_octal;

	iter = 2;
	codage_octal = map[(process->pos + 1) % MEM_SIZE];
	if (!map[(process->pos + iter) % MEM_SIZE] ||
			map[(process->pos + iter) % MEM_SIZE] > 16)
		return (TRUE);
	++iter;
	if (IS_T_REG_SECOND(codage_octal) &&
			(!map[(process->pos + iter) % MEM_SIZE] ||
			map[(process->pos + iter) % MEM_SIZE] > 16))
		return (TRUE);
	IS_T_REG_SECOND(codage_octal) ? (iter += 1) : 0;
	!IS_T_REG_SECOND(codage_octal) ? (iter += 2) : 0;
	if (IS_T_REG_THIRD(codage_octal) &&
			(!map[(process->pos + iter) % MEM_SIZE] ||
			map[(process->pos + iter) % MEM_SIZE] > 16))
		return (TRUE);
	if (!IS_T_REG_FIRST(codage_octal) || (codage_octal & 0x30) == 0x0 ||
			(!IS_T_REG_THIRD(codage_octal) && !IS_T_DIR_THIRD(codage_octal)))
		return (TRUE);
	return (FALSE);
}
