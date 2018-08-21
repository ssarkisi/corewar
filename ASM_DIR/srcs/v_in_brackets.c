/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_validation.o                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:26:57 by vhavryle          #+#    #+#             */
/*   Updated: 2018/04/20 15:26:58 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

char			*in_brackets(char **all, int s, int *row, char **tmp)
{
	int			i;
	int			e;
	char		*ret;

	e = ft_istrchr(&all[*row][s + 1], '"');
	if (e == -1)
		return (in_br_long(all, row, s, tmp));
	if ((i = get_print(all[*row], s + e + 2, -1)) != -1)
		er_exit("ERROR: unexpected character [", *row + 1, i + 1,
				free_ex(NULL, all, tmp, 1));
	ret = ft_strsub(all[*row], s + 1, e);
	return (ret);
}

char			*in_br_long(char **all, int *row, int s, char **tmp)
{
	char		*ret;
	int			t;
	int			e;

	e = -1;
	t = *row;
	while (e == -1 && all[++t])
		e = ft_istrchr(all[t], '"');
	if (in_br_errors(e, &all, t, tmp) == 0)
		return (NULL);
	ret = fjoin(ft_strsub(all[*row], s + 1,
						ft_strlen(&all[*row][s + 1])), "\n");
	while (++*row <= t)
	{
		ret = fjoin(ret, all[*row]);
		if (*row != t)
			ret = fjoin(ret, "\n");
	}
	ret[ft_strlen(ret) - 1] = '\0';
	*row = *row > t ? *row - 1 : *row;
	return (ret);
}

int				in_br_errors(int e, char ***all_p, int t, char **tmp)
{
	char		**all;
	int			i;

	all = *all_p;
	if (e == -1)
		er_exit("ERROR: unexpected character [", t + 1, e,
				free_ex(NULL, all, tmp, 1));
	if ((i = get_print(all[t], ft_istrchr(all[t], '"') + 1, -1)) != -1)
		er_exit("ERROR: unexpected character [", t + 1, i + 1,
				free_ex(NULL, all, tmp, 1));
	return (1);
}

char			*fjoin(char *s1, char *s2)
{
	char		*fresh;
	int			i;
	int			j;

	if (!s1 || !s2)
		return (NULL);
	j = 0;
	if ((fresh = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)) == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		fresh[j] = s1[j];
		j++;
	}
	i = j;
	j = -1;
	while (s2[++j] != '\0')
	{
		fresh[i] = s2[j];
		i++;
	}
	fresh[i] = '\0';
	ft_strdel(&s1);
	return (fresh);
}
