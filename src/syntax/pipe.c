/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 00:01:00 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/03 15:33:46 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pipe_begining(t_hell *mini)
{
	int	i;

	i = 0;
	while (mini->line[i] == ' ' || mini->line[i] == '\t')
		i++;
	if (mini->line[i] == '|')
		return (0);
	return (1);
}

int	pipe_middle(t_hell *mini)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (mini->line[i])
	{
		while (mini->line[i] && (mini->line[i] == ' ' || mini->line[i] == '\t'))
			i++;
		if (mini->line[i] == '"' || mini->line[i] == '\'')
		{
			flag++;
			i++;
			while (mini->line[i] != '"' && mini->line[i] != '\'')
				i++;
			flag++;
			if (flag % 2 != 0)
				return (0);
		}
		if (mini->line[i] == '|')
		{
			i++;
			while (mini->line[i] && (mini->line[i] == ' '
					|| mini->line[i] == '\t'))
				i++;
			if (!check_for_redirections(mini, i))
				return (0);
		}
		i++;
	}
	return (1);
}

int	pipe_ending(t_hell *mini)
{
	int	i;

	i = ft_strlen(mini->line) - 1;
	while (mini->line[i] == ' ' || mini->line[i] == '\t')
		i--;
	if (mini->line[i] == '|')
		return (0);
	return (1);
}
