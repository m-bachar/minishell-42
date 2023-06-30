/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_store.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:35:36 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/07 20:14:06 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_whitespaces(t_hell *mini)
{
	char		*result;
	int			j;
	size_t		i;

	j = 0;
	i = 0;
	result = malloc(sizeof(char) * MAX_SIZE);
	if (!result)
		return ;
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
	{
		free(result);
		return ;
	}
	ft_strcpy(mini->line, result);
	free(result);
}

void	split_and_store(char *line, t_list *mini)
{
	char	**splitted;
	int		i;

	i = 0;
	splitted = ft_split(line, ' ');
	mini = NULL;
	while (splitted[i])
	{
		ft_lstadd_back(&mini, ft_lstnew(splitted[i], i, 0));
		i++;
	}
	while (mini != NULL)
	{
		if (!strcmp(mini->data, "|"))
			mini->token = PIPE;
		else if (!strcmp(mini->data, "<<"))
			mini->token = HEREDOC;
		else if (!strcmp(mini->data, ">>"))
			mini->token = APPEND;
		else if (!strcmp(mini->data, "<"))
			mini->token = FILE_IN;
		else if (!strcmp(mini->data, ">"))
			mini->token = FILE_OUT;
		else
			mini->token = WORD;
		mini = mini->next;
	}
	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
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
