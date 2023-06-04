/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 00:00:20 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/04 23:17:41 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	heredoc_begining(t_hell *mini)
{
	int	i;

	i = 0;
	while (mini->line[i] == ' ' || mini->line[i] == '\t')
		i++;
	if (mini->line[i] == '<' && mini->line[i + 1] == '<')
	{
		i += 2;
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

int	heredoc_middle(t_hell *mini)
{
	int	i;
	int flag;

	i = 0;
	flag = 0;
	while (mini->line[i])
	{
		while (mini->line[i] && (mini->line[i] == ' ' || mini->line[i] == '\t'))
			i++;
		if (mini->line[i] == '"' || mini->line[i] == '\'')
		{
			flag++;
			i++;
			while (mini->line[i] && mini->line[i] != '"' && mini->line[i] != '\'')
				i++;
			flag++;
			if (flag % 2 != 0)
				return (0);
		}
		if (mini->line[i] == '<' && mini->line[i + 1] == '<')
		{
			i += 2;
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

int	heredoc_ending(t_hell *mini)
{
	int	i;

	i = ft_strlen(mini->line) - 1;
	while (mini->line[i] == ' ' || mini->line[i] == '\t')
		i--;
	if (mini->line[i] == '<' && mini->line[i - 1] == '<')
		return (0);
	return (1);
}
