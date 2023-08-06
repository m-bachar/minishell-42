/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell_entrance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:29:00 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/06 17:53:47 by mbachar          ###   ########.fr       */
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

int	redirection(t_list **head, t_env *env)
{
	t_list	*list = *head;
	int		i;

	if (open_and_heredoc(&list, &env))
		return (1);
	list = *head;
	while (list)
	{
		i = 0;
		while (list->command[i])
		{
			open_and_append(list->command[i], list->command[i + 1], list);
			open_and_output(list->command[i], list->command[i + 1], list);
			open_and_input(list->command[i], list->command[i + 1], list);
			i++;
		}
		list = list->next;
	}
	list = *head;
	remove_args_from_redirections(&list);
	remove_NUL(&list);
	list = *head;
	return (0);
}

void	minihell_entrance(t_hell *mini)
{
	t_env	*env;
	t_list	*list;
	char	*line;

	env = NULL;
	list = NULL;
	line = NULL;
	mini->line = NULL;
	rl_catch_signals = 0;
	printf(CYAN "\t\tHell is -- MiniShell 😔 😔  \n\n" RESET);
	copy_env(&env, mini->vne);
	while (1)
	{
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
			if (redirection(&list, env))
			{
				ft_clearmem(&list, &mini);
				continue ;
			}
			skip_or_replace(&list, &env, mini);
			if (list->command[0])
				commands(list, mini, &env);
			ft_clearmem(&list, &mini);
		}
	}
}
