/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:29:00 by mbachar           #+#    #+#             */
/*   Updated: 2023/05/26 05:07:21 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax(t_hell *mini, char *line)
{
	if (!all_begining_syntaxes(mini)
		|| !all_middle_syntaxes(mini) || !all_ending_syntaxes(mini))
		printf("😤 " RED "SyntaxError: " RESET
			"Oh dear! It appears you've encountered a syntax error.\n");
	add_history(mini->line);
	if (all_begining_syntaxes(mini)
		&& all_middle_syntaxes(mini) && all_ending_syntaxes(mini))
	{
		line = add_whitespaces(mini);
		split_and_store(line, mini->push);
	}
}

void	minihell_entrance(t_hell *mini)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	system("clear");
	printf(CYAN "\t\tHell is -- MiniShell 😔 😔  \n\n" RESET);
	while (1)
	{
		mini->line = readline("😃 " CYAN "Minihell-1.0$ " RESET);
		if (!mini->line)
			return (printf(RED "\t\tExiting Minishell 🥺\n" RESET), exit(0));
		if (!ft_strncmp(mini->line, "", 1)
			|| !remove_whitespaces_from_history(mini))
		{
			free(mini->line);
			continue ;
		}
		syntax(mini, line);
	}
}
