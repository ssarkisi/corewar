/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:59:30 by vhavryle          #+#    #+#             */
/*   Updated: 2018/05/15 15:59:32 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

char			**unex_error(int n)
{
	write(1, "ERROR unex: at line [", 16);
	ft_putnbr(n);
	write(1, "]\n", 2);
	return (NULL);
}

void			exterm_arr_com(char ***all)
{
	int			i;
	char		**tmp;

	tmp = *all;
	i = -1;
	while (tmp[++i])
		exterminate_comments(&tmp[i]);
}

void			exterminate_comments(char **str)
{
	int			com;
	char		*tmp;
	int			com2;

	tmp = *str;
	if (tmp != NULL)
	{
		com = ft_istrchr(tmp, COMMENT_CHAR);
		com2 = ft_istrchr(tmp, ';');
		if (com != -1 && com2 != -1)
		{
			com = com > com2 ? com2 : com;
			tmp[com] = '\0';
		}
		else if (com == -1 && com2 != -1)
		{
			com = com2;
			tmp[com] = '\0';
		}
		else if (com != -1)
			tmp[com] = '\0';
	}
}
