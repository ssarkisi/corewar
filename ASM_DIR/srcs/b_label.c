/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_label.o                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssarkisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:16:00 by ssarkisi          #+#    #+#             */
/*   Updated: 2018/04/23 13:16:01 by ssarkisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		get_way_size(t_ol *ol, int strn)
{
	int			size;
	t_ol		*tmp;

	size = 0;
	tmp = ol;
	while (tmp)
	{
		if (tmp->strn < strn)
			size += tmp->size;
		tmp = tmp->next;
	}
	return (size);
}

long	get_byte_to_lable(t_ol *ol, char *l, int size)
{
	t_ol		*ol2;
	int			f;
	long		n;

	f = 0;
	ol2 = ol->first;
	n = 65536;
	if (size == 4)
		n = 4294967296;
	while (ol2)
	{
		if (ft_str_in_array(l, ol2->label_name) == 1)
		{
			f = 1;
			break ;
		}
		ol2 = ol2->next;
	}
	if (f == 0 || ol->strn == ol2->strn)
		return (0);
	if (ol->strn > ol2->strn)
		return (n - get_way_size(ol2, ol->strn));
	else
		return (get_way_size(ol, ol2->strn));
}
