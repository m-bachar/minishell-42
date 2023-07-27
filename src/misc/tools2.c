/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 02:27:21 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/27 02:27:39 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return ((*s1) - (*s2));
		s1++;
		s2++;
	}
	return (0);
}

int	ft_strcmp2(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s2)
		return (0);
	if (!s1)
		s1 = ft_strdup("");
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (free(s1), 0);
}

int	ft_strlen2(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}
