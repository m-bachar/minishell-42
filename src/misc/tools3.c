/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:06:59 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/08 22:22:31 by mbachar          ###   ########.fr       */
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

void	ft_clearmem(t_list **lst, t_hell **mini)
{
	t_list	*tmp;
	t_list	*to_clear;

	tmp = *lst;
	free((*mini)->line);
	while (tmp)
	{
		to_clear = tmp;
		free(to_clear->multi_cmds);
		free_mem(to_clear->command);
		tmp = tmp->next;
		free(to_clear);
		to_clear = NULL;
	}
	*lst = NULL;
}

int	ft_strchr2(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	iswhitespace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}
