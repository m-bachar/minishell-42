/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:02:48 by mbachar           #+#    #+#             */
/*   Updated: 2023/05/25 02:22:46 by mbachar          ###   ########.fr       */
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
