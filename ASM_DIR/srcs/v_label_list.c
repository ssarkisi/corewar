/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_label_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:50:53 by vhavryle          #+#    #+#             */
/*   Updated: 2018/05/02 15:50:56 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			v_strncmp(char *s1, char *s2)
{
	int		i;
	int		j;

	i = 1;
	if (s1[i] == ':')
		i++;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[i] == s2[j] && s1[i] != '\0')
	{
		i++;
		j++;
	}
	if (s1[i] == '\0' && s2[j] == '\0')
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

int			find_str_in_array(char *str, char **arr)
{
	int		i;

	i = 0;
	if (str == NULL || arr == NULL || arr[0] == NULL)
		return (0);
	while (arr[i] != NULL)
	{
		if (arr[i] == NULL)
			return (0);
		if (v_strncmp(str, arr[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void		find_label_in_ol(char *arg, t_ol *ol, int strn, char **all)
{
	int		f;
	t_ol	*tmp;

	f = 0;
	tmp = ol;
	while (tmp)
	{
		if (find_str_in_array(arg, tmp->label_name) == 1)
		{
			f = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (f == 0)
	{
		ft_putstr("ERRORR: Label \"\0");
		ft_putstr(arg);
		ft_putstr("\" does not exist, line \0");
		ft_putnbr(strn + 1);
		write(1, "\n", 1);
		free_ex(g_list->first, NULL, all, 0);
	}
}

void		check_labels(t_ol *ol, char **all)
{
	t_ol	*tmp;

	tmp = ol->first;
	while (tmp)
	{
		if (tmp->argn > 0 && ((tmp->arg1[0] == '%' && tmp->arg1[1] == ':')
							|| tmp->arg1[0] == ':'))
			find_label_in_ol(tmp->arg1, tmp->first, tmp->strn, all);
		if (tmp->argn > 1 && ((tmp->arg2[0] == '%' && tmp->arg2[1] == ':')
							|| tmp->arg2[0] == ':'))
			find_label_in_ol(tmp->arg2, ol->first, tmp->strn, all);
		if (tmp->argn > 2 && ((tmp->arg3[0] == '%' && tmp->arg3[1] == ':')
							|| tmp->arg3[0] == ':'))
			find_label_in_ol(tmp->arg3, ol->first, tmp->strn, all);
		tmp = tmp->next;
	}
}
