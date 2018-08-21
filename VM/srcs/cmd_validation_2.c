/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validation_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 18:43:35 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/03 18:43:35 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

_Bool			ft_is_nonvalid_addsub(uint8_t *map, t_process *process)
{
	uint8_t		codage_octal;

	if (!map[(process->pos + 2) % MEM_SIZE] ||
		map[(process->pos + 2) % MEM_SIZE] > 16 ||
		!map[(process->pos + 3) % MEM_SIZE] ||
		map[(process->pos + 3) % MEM_SIZE] > 16 ||
		!map[(process->pos + 4) % MEM_SIZE] ||
		map[(process->pos + 4) % MEM_SIZE] > 16)
		return (TRUE);
	codage_octal = map[(process->pos + 1) % MEM_SIZE];
	if (!IS_T_REG_FIRST(codage_octal) || !IS_T_REG_SECOND(codage_octal) ||
		!IS_T_REG_THIRD(codage_octal))
		return (TRUE);
	return (FALSE);
}

_Bool			ft_is_nonvalid_conds(uint8_t *map, t_process *process)
{
	unsigned	iter;
	uint8_t		codage_octal;

	codage_octal = map[(process->pos + 1) % MEM_SIZE];
	if ((iter = 2) && IS_T_REG_FIRST(codage_octal) &&
		(!map[(process->pos + iter) % MEM_SIZE] ||
		map[(process->pos + iter) % MEM_SIZE] > 16))
		return (TRUE);
	IS_T_REG_FIRST(codage_octal) ? (iter += 1) : 0;
	IS_T_DIR_FIRST(codage_octal) ? (iter += 4) : 0;
	IS_T_IND_FIRST(codage_octal) ? (iter += 2) : 0;
	if (IS_T_REG_SECOND(codage_octal) &&
		(!map[(process->pos + iter) % MEM_SIZE] ||
		map[(process->pos + iter) % MEM_SIZE] > 16))
		return (TRUE);
	IS_T_REG_SECOND(codage_octal) ? (iter += 1) : 0;
	IS_T_DIR_SECOND(codage_octal) ? (iter += 4) : 0;
	IS_T_IND_SECOND(codage_octal) ? (iter += 2) : 0;
	if (!map[(process->pos + iter) % MEM_SIZE] ||
		map[(process->pos + iter) % MEM_SIZE] > 16)
		return (TRUE);
	if ((codage_octal & 0xc0) == 0x0 || (codage_octal & 0x30) == 0x0 ||
		!IS_T_REG_THIRD(codage_octal))
		return (TRUE);
	return (FALSE);
}

_Bool			ft_is_nonvalid_aff(uint8_t *map, t_process *process)
{
	uint8_t		codage_octal;

	codage_octal = map[(process->pos + 1) % MEM_SIZE];
	if (!IS_T_REG_FIRST(codage_octal) ||
		!(map[(process->pos + 2) % MEM_SIZE]) ||
		map[(process->pos + 2) % MEM_SIZE] > 16)
		return (TRUE);
	return (FALSE);
}
