/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_store.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:35:36 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/27 14:57:42 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*add_whitespaces(t_hell *mn)
{
	char		*result;

	mn->i = 0;
	mn->j = 0;
	result = ft_calloc(MAX_SIZE, sizeof(char));
	while (mn->i < ft_strlen2(mn->line))
	{
		if (isredirection(mn, mn->i))
		{
			result[mn->j++] = ' ';
			if (isredirection2(mn, mn->i))
				result[mn->j++] = mn->line[mn->i];
			if (mn->line[mn->i + 1] && mn->line[mn->i] == mn->line[mn->i + 1])
				mn->i++;
			result[mn->j++] = mn->line[mn->i];
			result[mn->j++] = ' ';
		}
		else
			result[mn->j++] = mn->line[mn->i];
		mn->i++;
	}
	free(mn->line);
	mn->line = ft_calloc(ft_strlen2(result) + 1, sizeof(char));
	ft_strcpy(mn->line, result);
	return (free(result), mn->line);
}

void	split_and_store(char *line, t_list **mini)
{
	char	**splitted;
	int		i;

	i = 0;
	splitted = ft_split(line, '|');
	if (splitted == NULL || splitted[0] == NULL)
		return ;
	while (splitted[i])
	{
		ft_lstadd_back(mini, ft_lstnew(splitted[i]));
		i++;
	}
	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;
	t_list	*to_clear;

	tmp = *lst;
	while (tmp)
	{
		to_clear = tmp;
		tmp = tmp->next;
		free(to_clear);
		// to_clear = NULL;
	}
	*lst = NULL;
}
