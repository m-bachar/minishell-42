/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:06:59 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/28 14:18:05 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	isredirection(t_hell *mini, int i)
{
	if (mini->line[i] == '<' || mini->line[i] == '>'
		|| mini->line[i] == '|')
		return (1);
	return (0);
}

int	isredirection2(t_hell *mini, int i)
{
	if ((mini->line[i] == '<' && mini->line[i + 1] == '<')
		|| (mini->line[i] == '>' && mini->line[i + 1] == '>')
		|| (mini->line[i] == '|' && mini->line[i + 1] == '|'))
		return (1);
	return (0);
}

void	ft_clearmem2(t_env **env)
{
	t_env	*tmp;
	t_env	*to_clear;

	tmp = *env;
	while (tmp)
	{
		to_clear = tmp;
		tmp = tmp->next;
		free(to_clear->env_name);
		free(to_clear->env_value);
		free(to_clear);
		to_clear = NULL;
	}
	*env = NULL;
}
