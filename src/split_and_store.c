/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_store.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:35:36 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/08 22:54:14 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_whitespaces(t_hell *mini)
{
	char		*result;
	int			j;
	size_t		i;

	j = 0;
	i = 0;
	result = malloc(sizeof(char) * MAX_SIZE);
	if (!result)
		return (NULL);
	while (i < ft_strlen(mini->line))
	{
		if (mini->line[i] == '<' || mini->line[i] == '>'
			|| mini->line[i] == '|')
		{
			result[j++] = ' ';
			if ((mini->line[i] == '<' && mini->line[i + 1] == '<')
				|| (mini->line[i] == '>' && mini->line[i + 1] == '>')
				|| (mini->line[i] == '|' && mini->line[i + 1] == '|'))
				result[j++] = mini->line[i];
			if (mini->line[i + 1] && mini->line[i] == mini->line[i + 1])
				i++;
			result[j++] = mini->line[i];
			result[j++] = ' ';
		}
		else
			result[j++] = mini->line[i];
		i++;
	}
	result[j] = '\0';
	free(mini->line);
	mini->line = malloc(sizeof(char) * ft_strlen(result) + 1);
	if (!mini->line)
		return (free(result), NULL);
	ft_strcpy(mini->line, result);
	return (free(result), mini->line);
}

void	split_and_store(char *line, t_list **mini)
{
	char	**splitted;
	int		i;

	i = 0;
	splitted = ft_split(line, '|');
	if(splitted == NULL || splitted[0] == NULL)
		return;
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
