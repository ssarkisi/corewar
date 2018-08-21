/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.o                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:21:19 by vhavryle          #+#    #+#             */
/*   Updated: 2017/11/09 15:21:22 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(const char *s)
{
	char	*new;
	int		i;
	int		e;

	new = NULL;
	if (s)
	{
		i = 0;
		while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
			i++;
		e = ft_strlen(s) - 1;
		while (s[e] == ' ' || s[e] == '\n' || s[e] == '\t')
			e--;
		if (s[i] == '\0' || (size_t)(i - 1) == ft_strlen(s))
		{
			new = ft_strnew(1);
			new[0] = '\0';
			return (new);
		}
		new = ft_strsub(s, i, e - i + 1);
	}
	return (new);
}
