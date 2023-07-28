/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell_entrance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:29:00 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/28 17:03:10 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_syntax_error(void)
{
	printf("😤 " RED "SyntaxError: " RESET
		"Oh dear! It appears you've encountered a syntax error.\n");
}

void	exit_minihell(t_hell *mini)
{
	printf(RED "\t\tExiting MiniShell 🥺\n" RESET);
	if (mini->line)
		free(mini->line);
	exit(0);
}

void	minihell_entrance(t_hell *mini)
{
	t_env	*lst;
	t_list	*list;
	char	*line;

	lst = NULL;
	list = NULL;
	line = NULL;
	mini->line = NULL;
	printf(CYAN "\t\tHell is -- MiniShell 😔 😔  \n\n" RESET);
	copy_env(&lst, mini->vne);
	while (1)
	{
		mini->line = readline("😃 Minihell-1.0$ ");
		if (!mini->line)
			exit_minihell(mini);
		if (!ft_strcmp(mini->line, "")
			|| !remove_whitespaces_from_history(mini))
		{
			free(mini->line);
			continue ;
		}
		shape_shifting(mini->line);
		if (!all_in_one(mini))
			print_syntax_error();
		shape_shifting(mini->line);
		add_history(mini->line);
		shape_shifting(mini->line);
		if (all_in_one(mini))
		{
			line = add_whitespaces(mini);
			split_and_store(line, &list);
			split_and_store2(&list);
			nodes_shapeshifting(&list);
			if (is_heredoc(list))
				open_and_heredoc(&list);
			else if (is_append(list))
				open_and_append(&list);
			else if (is_output(list))
				open_and_output(&list);
			else if (is_input(list))
				open_and_input(&list);
			skip_or_replace(&list, &lst, mini);
			commands(list, mini, lst);
			ft_clearmem(&list, &mini);
		}
	}
}
