/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:56:11 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/03 15:33:26 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	file_out_begining(t_hell *mini)
{
	int	i;

	i = 0;
	while (mini->line[i] == ' ' || mini->line[i] == '\t')
		i++;
	if (mini->line[i] == '>' && mini->line[i + 1] != '>')
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

int	file_out_middle(t_hell *mini)
{
	int	i;
	int	flag;

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
			while (mini->line[i] != '"' && mini->line[i] != '\'')
				i++;
			flag++;
			if (flag % 2 != 0)
				return (0);
		}
		if (mini->line[i] == '>' && mini->line[i + 1] != '>')
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

int	file_out_ending(t_hell *mini)
{
	int	i;

	i = ft_strlen(mini->line) - 1;
	while (mini->line[i] == ' ' || mini->line[i] == '\t')
		i--;
	if (mini->line[i] == '>')
		return (0);
	return (1);
}
