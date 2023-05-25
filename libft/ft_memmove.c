/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:34:57 by mbachar           #+#    #+#             */
/*   Updated: 2022/11/09 21:54:03 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*str1;
	char	*str2;
	int		i;

	str1 = (char *) src;
	str2 = (char *) dest;
	i = (int) len;
	if (dest > src)
	{
		i--;
		while (i >= 0)
		{
			str2[i] = str1[i];
			i--;
		}
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}
