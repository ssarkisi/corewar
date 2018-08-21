/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 19:28:46 by vhavryle          #+#    #+#             */
/*   Updated: 2018/04/18 19:28:47 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_ol		*new_e(char **label, char **args, int strn, int argn)
{
	t_ol	*new;
	int		i;
	int		l;

	if (!(new = malloc(sizeof(t_ol))))
		return (NULL);
	list_null(new, argn, strn);
	l = get_arr_size(label);
	if (l != 0)
	{
		new->label_name = malloc(sizeof(char *) * (l + 1));
		i = -1;
		while (new->label_name && label[++i] != NULL)
			new->label_name[i] = ft_strtrim(label[i]);
		new->label_name[i] = NULL;
	}
	if (args && args[0] != NULL)
		new->arg1 = ft_strtrim(args[0]);
	if (argn > 1 && args && args[1] != NULL)
		new->arg2 = ft_strtrim(args[1]);
	if (argn > 2 && args && args[2] != NULL)
		new->arg3 = ft_strtrim(args[2]);
	free_all_ar(&args);
	return (new);
}

void		list_null(t_ol *elem, int argn, int strn)
{
	elem->label_name = NULL;
	elem->arg1 = NULL;
	elem->arg2 = NULL;
	elem->arg3 = NULL;
	elem->next = NULL;
	elem->first = NULL;
	elem->argn = argn;
	elem->strn = strn;
}

void		push(t_ol *new, int opcode)
{
	t_ol	*tmp;

	tmp = g_list;
	if (!tmp)
	{
		g_list = new;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->first = g_list;
	new->opcode = opcode;
}
