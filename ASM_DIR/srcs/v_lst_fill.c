/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_lst_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:51:55 by vhavryle          #+#    #+#             */
/*   Updated: 2018/05/02 15:51:57 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			**mir_arr(int *i, int *r, int *m)
{
	int		**ret;

	ret = malloc(sizeof(int*) * 3);
	ret[0] = i;
	ret[1] = m;
	ret[2] = r;
	return (ret);
}

char		**if_lc_par(int **mass, char *lab, char **labels, char **all)
{
	if (*mass[2] == -1)
	{
		free(lab);
		er_exit("ERROR: at line [", *mass[0] + 1, -1,
				free_ex(g_list, labels, all, 1));
	}
	labels[*mass[1] - 1] = ft_strdup(lab);
	labels = realloc(labels, ++*mass[1] * sizeof(char*));
	labels[*mass[1] - 1] = NULL;
	if (!lable_com(labels, get_arr(all[*mass[0]], get_c_op(*mass[2]), "1"),
				*mass[0], NULL))
	{
		free(lab);
		free_ex(g_list, labels, all, 0);
	}
	free_str_arr(labels);
	*mass[1] = 1;
	ft_strdel(&lab);
	free(mass);
	return (get_null_arr(1));
}

char		**if_c_par(int **mass, char **labels, char **all)
{
	if (*mass[2] == -1)
		er_exit("ERROR: at line [", *mass[0] + 1, -1,
				free_ex(g_list, labels, all, 1));
	if (!lable_com(labels, get_arr(all[*mass[0]], get_c_op(*mass[2]), "0"),
				*mass[0], NULL))
		free_ex(g_list, labels, all, 0);
	free_str_arr(labels);
	*mass[1] = 1;
	free(mass);
	return (get_null_arr(1));
}

char		**re_arr(char **labels, int *m, char *lab)
{
	labels[*m - 1] = ft_strdup(lab);
	labels = realloc(labels, ++*m * sizeof(char*));
	labels[*m - 1] = NULL;
	ft_strdel(&lab);
	return (labels);
}

void		list_filling(char **all, int i, size_t m)
{
	char	**labels;
	char	*l;
	int		ret;
	int		lbc;

	lbc = -1;
	labels = get_null_arr(1);
	i = skip_comments(all, i) - 1;
	while (all[++i])
	{
		l = is_label(all[i], &lbc);
		if (l && (ret = s_is_comand(all[i], lbc + 1, 0, 0)) != 0)
			labels = if_lc_par(mir_arr(&i, &ret, (int*)&m), l, labels, all);
		else if (l != NULL && (ret = s_is_comand(all[i], lbc + 1, 0, 0)) == 0)
			labels = re_arr(labels, (int*)&m, l);
		else if (l == NULL && (ret = s_is_comand(all[i], 0, 0, 0)) != 0)
			labels = if_c_par(mir_arr(&i, &ret, (int*)&m), labels, all);
		else if (get_print(all[i], -1, -1) != -1)
			er_exit("ERROR: at line [", i + 1, -1, fr_fl(g_list, l, all, 1));
	}
	if (labels && labels[0] != NULL)
		push(new_e(labels, NULL, i, 0), -1);
	free_str_arr(labels);
}
