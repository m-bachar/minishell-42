/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:02:48 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/05 20:43:45 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_for_redirections(t_hell *mini, int i)
{
	if (mini->line[i] == '<' || mini->line[i] == '>'
		|| mini->line[i] == '|')
		return (0);
	return (1);
}

int	remove_whitespaces_from_history(t_hell *mini)
{
	int	i;

	i = 0;
	while (iswhitespace(mini->line[i]))
		i++;
	if (mini->line[i] == '\0')
		return (0);
	return (1);
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

void	shape_shifting(char	*line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i + 1] && (line[i] == '\"'))
		{
			i++;
			while (line[i] && (line[i] != '\"'))
			{
				line[i] *= -1;
				i++;
				if (!line[i])
					break ;
			}
		}
		if (!line[i])
			break ;
		i++;
	}
}

void	nodes_shapeshifting(t_list **mini)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *mini;
	while (*mini)
	{
		while ((*mini)->command[i])
		{
			shape_shifting((*mini)->command[i]);
			i++;
		}
		i = 0;
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
}
