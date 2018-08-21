/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_lib_overload.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:52:39 by vhavryle          #+#    #+#             */
/*   Updated: 2018/05/02 15:52:40 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			ft_istrchr(const char *s, int c)
{
	int		i;

	i = -1;
	if (s)
	{
		while (s[++i] != '\0')
			if (s[i] == c)
				return (i);
		if (c == '\0')
			return (i);
	}
	return (-1);
}

int			ft_istrstr(char *str, const char *to_find)
{
	int		i;
	int		j;

	i = 0;
	if (to_find[0] == '\0')
		return (-1);
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (i);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

int			get_arr_size(char **arr)
{
	int		i;

	i = 0;
	if (arr)
	{
		while (arr[i] && arr[i] != NULL)
			i++;
	}
	return (i);
}

int			get_print(char *str, int s, int e)
{
	int		i;

	i = s == -1 ? -1 : s;
	e = e == -1 ? '\0' : e + 1;
	if (s == -1)
	{
		while (str[++i] != '\0')
			if (ft_istab(str[i]) == 1)
				return (i);
	}
	else
	{
		while (str[s] != e)
		{
			if (ft_istab(str[s]) == 1)
				return (s);
			s++;
		}
	}
	return (-1);
}

int			get_nonprint(char *str, int s, int per)
{
	int		i;

	i = s == -1 ? 0 : s;
	if (per == 1)
	{
		while (str[i] != '\0' && ft_istab(str[i]) == 1 && str[i] != '%')
			i++;
	}
	else
	{
		while (str[i] != '\0' && ft_istab(str[i]) == 1)
			i++;
	}
	if (str[i] == '\0')
		return (-1);
	return (i);
}
