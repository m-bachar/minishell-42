/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:29:00 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/01 19:29:46 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minihell_entrance(t_hell *mini)
{
	t_env	*lst;
	char	*line;

	lst = NULL;
	line = NULL;
	system("clear");
	printf(CYAN "\t\tHell is -- MiniShell 😔 😔  \n\n" RESET);
	copy_env(&lst, mini->vne);
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
			&& all_middle_syntaxes(mini) && \
			all_ending_syntaxes(mini) && quotes(mini))
		{
			mini->splitted = ft_split(mini->line, ' ');
			line = add_whitespaces(mini);
			choose_and_acquire(mini, lst);
		}
		// execution(mini, lst);
	}
}
