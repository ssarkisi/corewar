/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_val.o                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssarkisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 16:40:59 by ssarkisi          #+#    #+#             */
/*   Updated: 2018/04/24 16:41:00 by ssarkisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		get_val_treg(char *arg)
{
	int		v;

	v = ft_atoin(arg, 1);
	return (v);
}

int		get_val_tdir(char *arg, int size)
{
	int		v;

	v = ft_atoin(arg, 1);
	if (size == 2)
		v = REVERSE_2_BYTES(v);
	if (size == 4)
		v = REVERSE_4_BYTES(v);
	return (v);
}

int		get_val_tind(char *arg)
{
	int		v;

	v = REVERSE_2_BYTES(ft_atoin(arg, 0));
	return (v);
}

int		get_val_lable(t_ol *ol, char *arg, int size)
{
	char	*tmp;
	int		i;
	int		j;
	long	ret;

	i = 0;
	j = 0;
	ret = 0;
	while (arg[i] != '\0' && arg[i] != ':')
		i++;
	tmp = ft_strnew(ft_strlen(arg) - 2);
	while (arg[++i] != '\0')
	{
		tmp[j] = arg[i];
		j++;
	}
	tmp[j] = '\0';
	ret = get_byte_to_lable(ol, tmp, size);
	if (size == 2)
		ret = REVERSE_2_BYTES(ret);
	else if (size == 4)
		ret = REVERSE_4_BYTES(ret);
	free(tmp);
	return (ret);
}

void	set_val(t_ol *ol, int a)
{
	char	*arg;
	int		size;
	int		type;
	int		val;

	arg = get_arg(ol, a);
	size = get_arg_size(ol, a);
	type = get_arg_type(ol, a);
	val = 0;
	if (type == 1)
		val = get_val_treg(arg);
	if (type == 2)
		val = get_val_tdir(arg, size);
	if (type == 3)
		val = get_val_tind(arg);
	if (type == 4)
		val = get_val_lable(ol, arg, size);
	if (a == 1)
		ol->val1 = val;
	else if (a == 2)
		ol->val2 = val;
	else if (a == 3)
		ol->val3 = val;
}
