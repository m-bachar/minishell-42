/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:29:00 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/07 20:47:07 by otchekai         ###   ########.fr       */
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
	printf(RED "\t\tExiting Minishell 🥺\n" RESET);
	free(mini->line);
	exit(0);
}

void	minihell_entrance(t_hell *mini)
{
	t_env	*lst;
	t_list	*list;
	char	*line;
	int		fd;

	lst = NULL;
	list = NULL;
	line = NULL;
	fd = 0;
	printf(CYAN "\t\tHell is -- MiniShell 😔 😔  \n\n" RESET);
	copy_env(&lst, mini->vne);
	while (1)
	{
		mini->line = readline("😃 Minihell-1.0$ ");
		if (!mini->line)
			exit_minihell(mini);
		if (!ft_strncmp(mini->line, "", 1)
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
			mini->splitted = ft_split(mini->line, ' ');
			line = add_whitespaces(mini);
			split_and_store(line, &list);
			fd = open_and_heredoc(&list);
			choose_and_acquire(mini, lst);
		}
	}
}
