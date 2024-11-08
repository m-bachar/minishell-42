/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:21:05 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/29 21:07:55 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*dst;

	len = ft_strlen(s1);
	dst = malloc(len * sizeof(char) + 1);
	if (!dst)
		return (NULL);
	dst[len] = '\0';
	ft_memcpy(dst, s1, len);
	return (dst);
}
