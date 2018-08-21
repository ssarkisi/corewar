/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_name_comment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:52:23 by vhavryle          #+#    #+#             */
/*   Updated: 2018/05/02 15:52:25 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			skip_comments(char **all, int s)
{
	while (all[s] && striscom(all[s]) == -1)
		s++;
	return (s);
}

char		*name_validation(char **all, int *rows, int p, char **tmp)
{
	int		i;
	int		r;

	i = 0;
	if (p != -1)
	{
		while (ft_istab(all[*rows][i]) == 0)
			i++;
		if (i != p)
			er_exit("ERROR: at [", *rows + 1, i + 1, free_ex(0, tmp, all, 1));
		i += ft_strlen(NAME_CMD_STRING);
		while (all[*rows][i] != '\0' && all[*rows][i] != '"')
		{
			r = *rows + 1;
			if (ft_istab(all[*rows][i]) == 1)
				er_exit("ERROR: at [", r, i + 1, free_ex(0, tmp, all, 1));
			i++;
		}
		return (in_brackets(all, i, rows, tmp));
	}
	return (NULL);
}

char		*comment_validation(char **all, int *row, int p, char **tmp)
{
	int		i;

	i = 0;
	if (p != -1)
	{
		while (ft_istab(all[*row][i]) == 0)
			i++;
		if (i != p)
			er_exit("ERROR: at [", *row + 1, i + 1, free_ex(0, tmp, all, 1));
		i += ft_strlen(COMMENT_CMD_STRING);
		while (all[*row][i] != '\0' && all[*row][i] != '"')
		{
			if (ft_istab(all[*row][i]) == 1)
				er_exit("ERROR: at [", *row + 1, ++i, free_ex(0, tmp, all, 1));
			i++;
		}
		return (in_brackets(all, i, row, tmp));
	}
	return (NULL);
}

int			check_size(char *name, char *cmment)
{
	if (ft_strlen(name) > PROG_NAME_LENGTH)
	{
		write(1, "Champion name too long (Max length ", 35);
		ft_putnbr(PROG_NAME_LENGTH);
		write(1, ")\n", 2);
		return (0);
	}
	else if (ft_strlen(cmment) > COMMENT_LENGTH)
	{
		write(1, "comment is  too long (Max length ", 33);
		ft_putnbr(COMMENT_LENGTH);
		write(1, ")\n", 2);
		return (0);
	}
	return (1);
}

void		validate_all(char **all, int rows, int i, int p)
{
	char	**tmp;

	tmp = get_null_arr(3);
	i = skip_comments(all, 0);
	while ((tmp[0] == NULL || tmp[1] == NULL) && i < rows)
	{
		if ((p = ft_istrstr(all[i], COMMENT_CMD_STRING)) != -1 && !tmp[1])
			tmp[1] = comment_validation(all, &i, p, tmp);
		else if ((p = ft_istrstr(all[i], NAME_CMD_STRING)) != -1 &&
				tmp[0] == NULL)
			tmp[0] = name_validation(all, &i, p, tmp);
		else if (striscom(all[i]) != -1)
			er_exit("ERROR: unexpected character at [",
					i + 1, -1, free_ex(0, tmp, all, 1));
		i = skip_comments(all, ++i);
	}
	if (!check_size(tmp[0], tmp[1]))
		free_ex(NULL, tmp, all, 0);
	exterm_arr_com(&all);
	list_filling(all, i, 1);
	if (g_list == NULL)
		er_exit("ERROR: perhaps there is no command\n",
				-1, -1, free_ex(g_list, NULL, all, 1));
	asmembler(g_list, all, tmp);
}
