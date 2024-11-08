/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 00:01:00 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/05 20:43:23 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pipe_begining(t_hell *mini)
{
	int	i;

	i = 0;
	while (iswhitespace(mini->line[i]))
		i++;
	if (mini->line[i] == '|')
		return (0);
	return (1);
}

int	pipe_middle(t_hell *mini)
{
	int	i;

	i = 0;
	while (mini->line[i])
	{
		while (mini->line[i] && iswhitespace(mini->line[i]))
			i++;
		if (mini->line[i] == '|')
		{
			i++;
			while (mini->line[i] && iswhitespace(mini->line[i]))
				i++;
			if (mini->line[i] == '|')
				return (0);
		}
		if (!mini->line[i])
			break ;
		i++;
	}
	return (1);
}

int	pipe_ending(t_hell *mini)
{
	int	i;

	i = ft_strlen(mini->line) - 1;
	while (iswhitespace(mini->line[i]))
		i--;
	if (mini->line[i] == '|')
		return (0);
	return (1);
}
