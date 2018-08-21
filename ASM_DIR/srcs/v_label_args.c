/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_label_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:50:33 by vhavryle          #+#    #+#             */
/*   Updated: 2018/05/02 15:50:37 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			t_dir_v(char *str, int s)
{
	int		p;

	p = s;
	s = get_print(str, s, -1);
	if (str[s] == DIRECT_CHAR)
	{
		if (str[++s] == LABEL_CHAR)
		{
			p = label_validate(str, s + 1, -1);
			if (p == -1 || (p = get_print(str, p, -1)) == -1)
				return (1);
		}
		else if (str[s] == '-' || ft_isdigit(str[s]))
		{
			if (str[s] == '-')
				s++;
			if ((p = istr_isd(str, s, -1)) == -1)
				return (1);
			if (!ft_istab(str[p]))
				if ((p = get_print(str, p, -1)) == -1)
					return (1);
		}
	}
	return (0);
}

int			t_reg_val(char *str, int s)
{
	int		p;
	int		nbr;

	s = get_print(str, s, -1);
	if (str[s] == 'r')
	{
		nbr = ft_atoi(&str[s + 1]);
		p = istr_isd(str, s + 1, -1);
		if (nbr > 0 && nbr <= REG_NUMBER)
			if (p == -1 || !ft_istab(str[p]))
				if (p == -1 || (p = get_print(str, p, -1)) == -1)
					return (1);
	}
	return (0);
}

int			t_ind_val(char *str, int s)
{
	int		p;

	p = s;
	s = get_print(str, s, -1);
	if (str[s] == LABEL_CHAR)
	{
		p = label_validate(str, s + 1, -1);
		if (p == -1 || (p = get_print(str, p, -1)) == -1)
			return (1);
	}
	else if (str[s] == '-' || ft_isdigit(str[s]))
	{
		if (str[s] == '-')
			s++;
		if ((p = istr_isd(str, s, -1)) == -1)
			return (1);
		if (!ft_istab(str[p]))
			if ((p = get_print(str, p, -1)) == -1)
				return (1);
	}
	return (0);
}

char		*is_label(char *str, int *lbc)
{
	int		s;

	*lbc = ft_istrchr(str, LABEL_CHAR);
	if (*lbc != -1)
	{
		s = get_print(str, 0, -1);
		if (label_validate(str, s, *lbc - 1) == -1)
		{
			return (ft_strsub(str, s, *lbc - s));
		}
	}
	return (NULL);
}

int			label_validate(char *str, int s, int e)
{
	int		i;

	i = s;
	e = e == -1 ? '\0' : e + 1;
	while (str[i] != e && is_lb_ch(str[i]))
		i++;
	if (str[i] == '\0' || i == e)
		return (-1);
	return (i);
}
