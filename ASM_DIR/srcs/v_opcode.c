/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_opcode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 19:06:27 by vhavryle          #+#    #+#             */
/*   Updated: 2018/05/14 19:06:28 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

unsigned short	get_opcode(char *command)
{
	if (ft_strequ(LIVE, command))
		return (1);
	else if (ft_strequ(LD, command))
		return (2);
	else if (ft_strequ(ST, command))
		return (3);
	else if (ft_strequ(ADD, command))
		return (4);
	else if (ft_strequ(SUB, command))
		return (5);
	else if (ft_strequ(AND, command))
		return (6);
	else if (ft_strequ(OR, command))
		return (7);
	else if (ft_strequ(XOR, command))
		return (8);
	else if (ft_strequ(ZJMP, command))
		return (9);
	else if (ft_strequ(LDI, command))
		return (10);
	else if (ft_strequ(STI, command))
		return (11);
	return (get_opcode_co(command));
}

unsigned short	get_opcode_co(char *command)
{
	if (ft_strequ(FORK, command))
		return (12);
	else if (ft_strequ(LLD, command))
		return (13);
	else if (ft_strequ(LLDI, command))
		return (14);
	else if (ft_strequ(LFORK, command))
		return (15);
	else if (ft_strequ(AFF, command))
		return (16);
	return (0);
}

char			*get_c_op2(int op)
{
	if (op == 12)
		return (ft_strdup(FORK));
	else if (op == 13)
		return (ft_strdup(LLD));
	else if (op == 14)
		return (ft_strdup(LLDI));
	else if (op == 15)
		return (ft_strdup(LFORK));
	else if (op == 16)
		return (ft_strdup(AFF));
	return (NULL);
}

char			*get_c_op(int op)
{
	if (op == 1)
		return (ft_strdup(LIVE));
	else if (op == 2)
		return (ft_strdup(LD));
	else if (op == 3)
		return (ft_strdup(ST));
	else if (op == 4)
		return (ft_strdup(ADD));
	else if (op == 5)
		return (ft_strdup(SUB));
	else if (op == 6)
		return (ft_strdup(AND));
	else if (op == 7)
		return (ft_strdup(OR));
	else if (op == 8)
		return (ft_strdup(XOR));
	else if (op == 9)
		return (ft_strdup(ZJMP));
	else if (op == 10)
		return (ft_strdup(LDI));
	else if (op == 11)
		return (ft_strdup(STI));
	return (get_c_op2(op));
}
