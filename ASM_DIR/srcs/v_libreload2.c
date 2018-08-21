/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_libreload2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:55:38 by vhavryle          #+#    #+#             */
/*   Updated: 2018/05/15 15:55:40 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

char				**arg_nbr_er(char **spl, int get, int n, int exp)
{
	ft_putstr("ERROR: invalid args number, expected ");
	ft_putnbr(exp);
	write(1, " but get ", 9);
	ft_putnbr(get);
	write(1, " , at line [", 12);
	ft_putnbr(n);
	write(1, "]\n", 2);
	if (spl)
		free_str_arr(spl);
	return (NULL);
}

int					get_c_nbr(char *str, char c)
{
	int				i;
	int				ret;

	ret = 0;
	i = -1;
	if (str)
	{
		while (str[++i] != '\0')
			if (str[i] == c)
				ret++;
	}
	return (ret);
}

int					is_lb_ch(char c)
{
	int				i;

	i = -1;
	while (LABEL_CHARS[++i] != '\0')
	{
		if (LABEL_CHARS[i] == c)
			return (1);
	}
	return (0);
}

char				**get_null_arr(unsigned int len)
{
	char			**new;
	unsigned int	i;

	new = NULL;
	if (len != 0)
	{
		i = 0;
		if (!(new = malloc(sizeof(char*) * len)))
			return (NULL);
		while (i < len)
		{
			new[i] = NULL;
			i++;
		}
	}
	return (new);
}

int					istr_isd(char *str, int s, int e)
{
	if (e == -1)
		e = '\0';
	else
		e++;
	while (str[s] != e)
	{
		if (!ft_isdigit(str[s]))
			return (s);
		s++;
	}
	return (-1);
}
