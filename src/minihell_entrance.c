/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell_entrance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:29:00 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/05 18:25:48 by mbachar          ###   ########.fr       */
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
	int		file_in;
	int		append;

	lst = NULL;
	list = NULL;
	line = NULL;
	mini->line = NULL;
	rl_catch_signals = 0;
	printf(CYAN "\t\tHell is -- MiniShell 😔 😔  \n\n" RESET);
	copy_env(&lst, mini->vne);
	while (1)
	{
		file_in = 1;
		append = 1;
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
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
				open_and_heredoc(&list, &lst);
			if (is_append(list))
				append = open_and_append(&list);
			if (is_output(list))
				open_and_output(&list);
			if (is_input(list))
				file_in = open_and_input(&list);
			skip_or_replace(&list, &lst, mini);
			if (file_in == 1 && append == 1 && list->command[0])
				commands(list, mini, &lst);
			int i = 0;
			while (list)
			{
				while (list->command[i])
				{
					printf("cmd = %s\n", list->command[i]);
					i++;
				}
				i = 0;
				list = list->next;
			}
			ft_clearmem(&list, &mini);
		}
	}
}
