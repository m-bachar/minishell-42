/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:29:00 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/30 16:45:18 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minihell_entrance(t_hell *mini)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	system("clear");
	printf(CYAN "\t\tHell is -- MiniShell 😔 😔  \n\n" RESET);
	while (1)
	{
		mini->line = readline("😃 Minihell-1.0$ ");
		if (!mini->line)
			return (printf(RED "\t\tExiting Minishell 🥺\n" RESET),
				free(mini->line), exit(0));
		if (!ft_strncmp(mini->line, "", 1)
			|| !remove_whitespaces_from_history(mini))
		{
			free(mini->line);
			continue ;
		}
		if (!all_begining_syntaxes(mini)
			|| !all_middle_syntaxes(mini)
			|| !all_ending_syntaxes(mini) || !quotes(mini))
			printf("😤 " RED "SyntaxError: " RESET
				"Oh dear! It appears you've encountered a syntax error.\n");
		add_history(mini->line);
		if (all_begining_syntaxes(mini)
			&& all_middle_syntaxes(mini)
			&& all_ending_syntaxes(mini) && quotes(mini))
		{
			shape_shifting(mini->line);
			add_whitespaces(mini);
			split = ft_split(mini->line, ' ');
			mini->line = ft_strdup("");
			while (split[i])
			{
				mini->line = ft_strjoin(mini->line, split[i]);
				mini->line = ft_strjoin(mini->line, " ");
				i++;
			}
			split = ft_split(mini->line, '|');
			i = 0;
			while (split[i])
			{
				shape_shifting(split[i]);
				printf("%s\n", split[i]);
				i++;
			}
			i = 0;
		}
	}
}
