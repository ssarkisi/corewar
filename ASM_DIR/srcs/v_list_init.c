/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_list_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:51:35 by vhavryle          #+#    #+#             */
/*   Updated: 2018/05/02 15:51:37 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

char		**get_arr(char *line, char *com, char *is_l)
{
	char	**ret;

	ret = malloc(sizeof(char*) * 4);
	ret[3] = NULL;
	ret[0] = ft_strdup(line);
	ret[1] = ft_strdup(com);
	ret[2] = ft_strdup(is_l);
	ft_strdel(&com);
	return (ret);
}

int			lable_com(char **labels, char **arr, int nstr, char **tmp)
{
	int		islb;
	int		op;

	islb = ft_atoi(arr[2]);
	op = get_opcode(arr[1]);
	if (op == 1 || op == 9 || op == 12 || op == 15)
		tmp = v_lzfl(arr[0], arr[1], islb, nstr);
	else if (op == 4 || op == 5)
		tmp = v_add_sub(arr[0], arr[1], islb, nstr);
	else if (op == 6 || op == 7 || op == 8)
		tmp = v_and_or_xor(arr[0], arr[1], islb, nstr);
	else if (op == 10 || op == 14)
		tmp = v_ldi_lldi(arr[0], arr[1], islb, nstr);
	else if (op == 2 || op == 13)
		tmp = v_ld_lld(arr[0], arr[1], islb, nstr);
	else if (op == 3)
		tmp = v_st(arr[0], arr[1], islb, nstr);
	else if (op == 11)
		tmp = v_sti(arr[0], arr[1], islb, nstr);
	else if (op == 16)
		tmp = v_aff(arr[0], arr[1], islb, nstr);
	if (free_all_ar(&arr) && tmp == NULL)
		return (0);
	push(new_e(labels, tmp, nstr, get_arr_size(tmp)), op);
	return (1);
}

char		**arg_error(int argnbr, int line_nbr, char **spl)
{
	write(1, "ERROR: invlaid ", 15);
	ft_putnbr(argnbr);
	write(1, " argument, line ", 16);
	ft_putnbr(line_nbr + 1);
	write(1, "\n", 1);
	if (spl)
		free_str_arr(spl);
	return (NULL);
}

int			striscom(char *str)
{
	char	*tmp;
	int		ret;

	if (str == NULL)
		return (-1);
	tmp = ft_strdup(str);
	exterminate_comments(&tmp);
	if ((ret = get_print(tmp, -1, -1)) != -1)
	{
		ft_strdel(&tmp);
		return (ret);
	}
	ft_strdel(&tmp);
	return (-1);
}
