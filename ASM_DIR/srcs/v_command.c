/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:53:03 by vhavryle          #+#    #+#             */
/*   Updated: 2018/05/02 15:53:04 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

char		**v_lzfl(char *line, char *com, int isl, int n)
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
	if (t_dir_v(spl[0], 0) == 0)
		return (arg_error(1, n, spl));
	return (spl);
}

char		**v_add_sub(char *line, char *com, int isl, int n)
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
	if (na != 3 || (na = get_c_nbr(&line[p], SEPARATOR_CHAR) + 1) != 3)
		return (arg_nbr_er(spl, na, ++n, 3));
	if (t_reg_val(spl[0], 0) == 0)
		return (arg_error(1, n, spl));
	if (t_reg_val(spl[1], 0) == 0)
		return (arg_error(2, n, spl));
	if (t_reg_val(spl[2], 0) == 0)
		return (arg_error(3, n, spl));
	return (spl);
}

char		**v_and_or_xor(char *line, char *com, int isl, int n)
{
	char	**spl;
	int		p;
	int		na;
	int		i;

	p = 0;
	if (isl)
		p = ft_istrchr(line, LABEL_CHAR);
	p = ft_istrstr(&line[p], com) + p;
	p = get_nonprint(line, p, 1);
	if (p == -1)
		return (unex_error(n + 1));
	spl = ft_strsplit(&line[p], SEPARATOR_CHAR);
	na = get_arr_size(spl);
	if (na != 3 || (na = get_c_nbr(&line[p], SEPARATOR_CHAR) + 1) != 3)
		return (arg_nbr_er(spl, na, ++n, 3));
	i = -1;
	while (spl[++i])
		if (!t_reg_val(spl[i], 0) && !t_dir_v(spl[i], 0) &&
				!t_ind_val(spl[i], 0))
			return (arg_error(i + 1, n, spl));
	return (spl);
}

char		**v_ldi_lldi(char *line, char *com, int isl, int n)
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
	if (na != 3 || (na = get_c_nbr(&line[p], SEPARATOR_CHAR) + 1) != 3)
		return (arg_nbr_er(spl, na, ++n, 3));
	if (!t_reg_val(spl[0], 0) && !t_dir_v(spl[0], 0) &&
			!t_ind_val(spl[0], 0))
		return (arg_error(1, n, spl));
	if (!t_reg_val(spl[1], 0) && !t_dir_v(spl[1], 0))
		return (arg_error(2, n, spl));
	if (!t_reg_val(spl[2], 0))
		return (arg_error(3, n, spl));
	return (spl);
}

char		**v_ld_lld(char *line, char *com, int isl, int n)
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
	if (!t_dir_v(spl[0], 0) && !t_ind_val(spl[0], 0))
		return (arg_error(1, n, spl));
	if (!t_reg_val(spl[1], 0))
		return (arg_error(1, n, spl));
	return (spl);
}
