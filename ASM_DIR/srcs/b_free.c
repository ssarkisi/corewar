/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_free.o                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssarkisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 10:53:17 by ssarkisi          #+#    #+#             */
/*   Updated: 2018/04/26 10:53:19 by ssarkisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	free_str_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr && arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
}

void	free_ol(t_ol *ol)
{
	t_ol	*tmp;

	ol = ol->first;
	tmp = ol;
	while (tmp)
	{
		free_str_arr(tmp->label_name);
		if (tmp->arg1)
			free(tmp->arg1);
		if (tmp->arg2)
			free(tmp->arg2);
		if (tmp->arg3)
			free(tmp->arg3);
		if (tmp->code)
			free(tmp->code);
		ol = ol->next;
		free(tmp);
		tmp = ol;
	}
	free(ol);
}

void	free_all(t_ol *ol, char **name, char **comment)
{
	if (name && *name)
	{
		free(*name);
		*name = NULL;
	}
	if (comment && *comment)
	{
		free(*comment);
		*comment = NULL;
	}
	if (g_bin_file_name)
		free(g_bin_file_name);
	free_ol(ol);
}
