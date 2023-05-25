/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 08:36:02 by mbachar           #+#    #+#             */
/*   Updated: 2022/11/12 10:59:13 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	int		i;
	size_t	j;
	int		output;

	if (dest == 0 && n == 0)
		return (ft_strlen(src));
	output = (ft_strlen(src) + ft_strlen(dest));
	if (((n - 1) < ft_strlen(dest)) || n == 0)
		return (ft_strlen(src) + n);
	j = ft_strlen(dest);
	i = 0;
	while (j < n - 1 && src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (output);
}
