/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:53:27 by vhavryle          #+#    #+#             */
/*   Updated: 2018/05/02 15:53:29 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			free_all_ar(char ***all)
{
	char		**tmp;
	int			i;
	int			len;

	len = get_arr_size(*all);
	i = -1;
	tmp = *all;
	if (*all && tmp[0])
	{
		while (++i < len && tmp[i] != NULL)
			free(tmp[i]);
		free(*all);
	}
	return (1);
}

void		free_vol(t_ol *ol)
{
	t_ol	*tmp;

	ol = g_list->first;
	tmp = ol;
	while (tmp)
	{
		free_all_ar(&tmp->label_name);
		if (tmp->arg1)
			free(tmp->arg1);
		if (tmp->arg2)
			free(tmp->arg2);
		if (tmp->arg3)
			free(tmp->arg3);
		ol = ol->next;
		free(tmp);
		tmp = ol;
	}
	free(ol);
}

void		*free_ex(t_ol *ol, char **tmp, char **all, int ex)
{
	free_all_ar(&tmp);
	free_str_arr(all);
	if (g_bin_file_name)
		free(g_bin_file_name);
	if (ol != NULL)
		free_vol(ol);
	if (ex == 0)
		exit(0);
	return (NULL);
}

void		*fr_fl(t_ol *ol, char *line, char **all, int ex)
{
	ft_strdel(&line);
	free_all_ar(&all);
	if (g_bin_file_name)
		free(g_bin_file_name);
	if (ol != NULL)
		free_vol(ol);
	if (ex == 0)
		exit(0);
	return (NULL);
}

void		er_exit(char *text, int r, int c, void *trash)
{
	write(1, text, ft_strlen(text));
	if (r > -1)
	{
		ft_putnbr(r);
		write(1, "][", 2);
		if (c > -1)
			ft_putnbr(c);
		else
			write(1, "no info", 7);
		write(1, "]\n", 2);
	}
	trash = NULL;
	exit(0);
}
