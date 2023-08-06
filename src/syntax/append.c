/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:37:39 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/05 20:41:23 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	append_begining(t_hell *mini)
{
	int	i;

	i = 0;
	while (iswhitespace(mini->line[i]))
		i++;
	if (mini->line[i] == '>' && mini->line[i + 1] == '>')
	{
		i += 2;
		if (mini->line[i] == '\0')
			return (0);
		while (mini->line[i])
		{
			while (mini->line[i] && iswhitespace(mini->line[i]))
				i++;
			if (check_for_redirections(mini, i) && !iswhitespace(mini->line[i]))
				break ;
			if (!check_for_redirections(mini, i))
				return (0);
			i++;
		}
	}
	return (1);
}

int	append_middle(t_hell *mini)
{
	int	i;

	i = 0;
	while (mini->line[i])
	{
		while (mini->line[i] && iswhitespace(mini->line[i]))
			i++;
		if (mini->line[i] == '>' && mini->line[i + 1] == '>')
		{
			i += 2;
			while (mini->line[i] && iswhitespace(mini->line[i]))
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

int	append_ending(t_hell *mini)
{
	int	i;

	i = ft_strlen(mini->line) - 1;
	while (iswhitespace(mini->line[i]))
		i--;
	if (mini->line[i] == '>' && mini->line[i - 1] == '>')
		return (0);
	return (1);
}
