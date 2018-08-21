/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_ft.o                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssarkisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 17:50:00 by ssarkisi          #+#    #+#             */
/*   Updated: 2018/04/22 17:50:01 by ssarkisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			ft_strcmp1(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int			ft_str_in_array(char *str, char **arr)
{
	int		i;

	i = 0;
	if (str == NULL || arr == NULL || arr[0] == NULL)
		return (0);
	while (arr && arr[i] != NULL)
	{
		if (str == NULL || arr == NULL || arr[i] == NULL)
			return (0);
		if (ft_strcmp1(str, arr[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int			ft_atoin(char *str, int n)
{
	size_t				i;
	int					sign;
	unsigned long int	res;

	i = n;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
		str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] != '\0') && ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - '0');
		if (res >= 9223372036854775807 && sign == 1)
			return (-1);
		else if (res > 9223372036854775807 && sign == -1)
			return (0);
		i++;
	}
	return ((int)(res * sign));
}

int			*ft_get_zero_arr(int n)
{
	int		i;
	int		*arr;

	arr = malloc(sizeof(int) * n);
	i = 0;
	while (i < n)
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}

int			ft_istab(int c)
{
	if (c == ' ' || c == '\t')
		return (0);
	return (1);
}
