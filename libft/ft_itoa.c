/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:38:00 by mbachar           #+#    #+#             */
/*   Updated: 2022/11/15 22:49:40 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	number_len(int nbr)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr != '\0')
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*itoa;
	int		j;

	if (!n)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = number_len(n);
	j = 0;
	itoa = malloc((i) * sizeof(char) + 1);
	if (!itoa)
		return (NULL);
	if (n < 0)
	{
		itoa[j++] = '-';
		n *= -1;
	}
	itoa[i] = '\0';
	while (i-- > j)
	{
		itoa[i] = (n % 10) + 48;
		n /= 10;
	}
	return (itoa);
}
