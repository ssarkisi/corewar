/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_command2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:53:13 by vhavryle          #+#    #+#             */
/*   Updated: 2018/05/02 15:53:14 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			s_is_comand(char *str, int s, int ret, int e)
{
	char	*tmp;

	s = get_print(str, s, -1);
	e = get_nonprint(str, s, 1);
	if (s == -1)
		return (0);
	if (e < 0)
		return (-1);
	e -= 1;
	tmp = ft_strsub(str, s, e - s + 1);
	if (ft_strequ(LIVE, tmp))
		ret = 1;
	else if (ft_strequ(LD, tmp))
		ret = 2;
	else if (ft_strequ(ST, tmp))
		ret = 3;
	else if (ft_strequ(ADD, tmp))
		ret = 4;
	else if (ft_strequ(SUB, tmp))
		ret = 5;
	else
		ret = str_is_com2(tmp);
	ft_strdel(&tmp);
	return (ret);
}

int			str_is_com2(char *tmp)
{
	if (ft_strequ(AND, tmp))
		return (6);
	else if (ft_strequ(OR, tmp))
		return (7);
	else if (ft_strequ(XOR, tmp))
		return (8);
	else if (ft_strequ(ZJMP, tmp))
		return (9);
	else if (ft_strequ(LDI, tmp))
		return (10);
	else if (ft_strequ(STI, tmp))
		return (11);
	else if (ft_strequ(FORK, tmp))
		return (12);
	else if (ft_strequ(LLD, tmp))
		return (13);
	else if (ft_strequ(LLDI, tmp))
		return (14);
	else if (ft_strequ(LFORK, tmp))
		return (15);
	else if (ft_strequ(AFF, tmp))
		return (16);
	if (get_print(tmp, 0, -1) != -1)
		return (-1);
	return (0);
}

char		**v_sti(char *line, char *com, int isl, int n)
{
	char	**spl;
	int		p;
	int		na;

	p = 0;
	if (isl)
		p = ft_istrchr(line, LABEL_CHAR);
	p = ft_istrstr(&line[p], com) + p;
	p = get_nonprint(line, p, 1);
	if (p == -1)
		return (unex_error(n + 1));
	spl = ft_strsplit(&line[p], SEPARATOR_CHAR);
	na = get_arr_size(spl);
	if (na != 3 || ((na = get_c_nbr(&line[p], SEPARATOR_CHAR) + 1)) != 3)
		return (arg_nbr_er(spl, na, ++n, 3));
	if (!t_reg_val(spl[0], 0))
		return (arg_error(1, n, spl));
	if (!t_reg_val(spl[1], 0) && !t_ind_val(spl[1], 0) && !t_dir_v(spl[1], 0))
		return (arg_error(2, n, spl));
	if (!t_reg_val(spl[2], 0) && !t_dir_v(spl[2], 0))
		return (arg_error(3, n, spl));
	return (spl);
}

char		**v_aff(char *line, char *com, int isl, int n)
{
	char	**spl;
	int		p;
	int		na;

	p = 0;
	if (isl)
		p = ft_istrchr(line, LABEL_CHAR);
	p = ft_istrstr(&line[p], com) + p;
	p = get_nonprint(line, p, 1);
	if (p == -1)
		return (unex_error(n + 1));
	spl = ft_strsplit(&line[p], SEPARATOR_CHAR);
	na = get_arr_size(spl);
	if (na != 1 || (na = get_c_nbr(&line[p], SEPARATOR_CHAR) + 1) != 1)
		return (arg_nbr_er(spl, na, ++n, 1));
	if (!t_reg_val(spl[0], 0))
		return (arg_error(1, n, spl));
	return (spl);
}

char		**v_st(char *line, char *com, int isl, int n)
{
	char	**spl;
	int		p;
	int		na;

	p = 0;
	if (isl)
		p = ft_istrchr(line, LABEL_CHAR);
	p = ft_istrstr(&line[p], com) + p;
	p = get_nonprint(line, p, 1);
	if (p == -1)
		return (unex_error(n + 1));
	spl = ft_strsplit(&line[p], SEPARATOR_CHAR);
	na = get_arr_size(spl);
	if (na != 2 || (na = get_c_nbr(&line[p], SEPARATOR_CHAR) + 1) != 2)
		return (arg_nbr_er(spl, na, ++n, 2));
	if (!t_reg_val(spl[0], 0))
		return (arg_error(1, n, spl));
	if (!t_reg_val(spl[1], 0) && !t_ind_val(spl[1], 0))
		return (arg_error(2, n, spl));
	return (spl);
}
