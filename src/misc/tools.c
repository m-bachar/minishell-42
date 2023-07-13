/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:02:48 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/12 17:43:30 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	remove_whitespaces_from_history(t_hell *mini)
{
	int	i;

	i = 0;
	while (mini->line[i] == ' '
		|| (mini->line[i] >= '\t' && mini->line[i] <= '\r'))
		i++;
	if (mini->line[i] == '\0')
		return (0);
	return (1);
}

int	check_for_redirections(t_hell *mini, int i)
{
	if (mini->line[i] == '<' || mini->line[i] == '>'
		|| mini->line[i] == '|')
		return (0);
	return (1);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
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
