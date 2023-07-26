/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benito <benito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:52:11 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/25 10:52:06 by benito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	file_in_begining(t_hell *mini)
{
	int	i;

	i = 0;
	while (mini->line[i] == ' ' || mini->line[i] == '\t')
		i++;
	if (mini->line[i] == '<' && mini->line[i + 1] != '<')
	{
		i++;
		if (mini->line[i] == '\0')
			return (0);
		while (mini->line[i])
		{
			while (mini->line[i] && (mini->line[i] == ' '
					|| mini->line[i] == '\t'))
				i++;
			if (check_for_redirections(mini, i)
				&& mini->line[i] != ' ' && mini->line[i] != '\t')
				break ;
			if (!check_for_redirections(mini, i))
				return (0);
			i++;
		}
	}
	return (1);
}

int	file_in_middle(t_hell *mini)
{
	int	i;

	i = 0;
	while (mini->line[i])
	{
		while (mini->line[i] && (mini->line[i] == ' ' || mini->line[i] == '\t'))
			i++;
		if (mini->line[i] == '<' && mini->line[i + 1] != '<')
		{
			i++;
			while (mini->line[i] && (mini->line[i] == ' '
					|| mini->line[i] == '\t'))
				i++;
			if (!check_for_redirections(mini, i))
				return (0);
		}
		if (!mini->line[i])
			break ;
		i++;
	}
	return (1);
}

int	file_in_ending(t_hell *mini)
{
	int	i;

	i = ft_strlen(mini->line) - 1;
	while (mini->line[i] == ' ' || mini->line[i] == '\t')
		i--;
	if (mini->line[i] == '<')
		return (0);
	return (1);
}
