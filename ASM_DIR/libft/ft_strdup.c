/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.o                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 12:08:30 by vhavryle          #+#    #+#             */
/*   Updated: 2017/10/26 12:08:32 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(char *src)
{
	char	*copy;
	int		i;
	int		l;

	copy = NULL;
	if (src)
	{
		l = ft_strlen(src);
		i = -1;
		if (!(copy = (char*)malloc(l + 1)))
			return (NULL);
		while (++i < l)
		{
			copy[i] = src[i];
		}
		copy[i] = '\0';
	}
	return (copy);
}
