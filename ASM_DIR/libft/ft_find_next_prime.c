/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.o                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:50:05 by vhavryle          #+#    #+#             */
/*   Updated: 2017/11/16 12:50:06 by vhavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_find_next_prime(int nb)
{
	int	i;

	i = 0;
	nb++;
	while (i != 1)
	{
		if (ft_isprime(nb) == 1)
			return (nb);
		nb++;
	}
	return (0);
}