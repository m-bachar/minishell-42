/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_store.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:35:36 by mbachar           #+#    #+#             */
/*   Updated: 2023/05/25 02:21:46 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_whitespaces(t_hell *mini)
{
	char		result[MAX_SIZE];
	int			j;
	size_t		i;

	j = 0;
	i = 0;
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
	ft_strcpy(mini->line, result);
	return (mini->line);
}

void	split_and_store(char *line, t_list *mini)
{
	int		i;
	char	**splitted;

	i = 0;
	splitted = ft_split(line, ' ');
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
		printf("Cmd = %s\t\tCmd token = %d\n", mini->data, mini->token);
		mini = mini->next;
	}
}
