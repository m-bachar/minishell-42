/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:29:00 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/11 20:20:17 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	nodes_shapeshifting(t_list **mini)
// {
// 	t_list	*tmp;

// 	tmp = *mini;
// 	while (*mini)
// 	{
// 		shape_shifting((*mini)->data);
// 		(*mini) = (*mini)->next;
// 	}
// 	*mini = tmp;
// }

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

void	split_and_store2(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (*list)
	{
		(*list)->command = ft_split((*list)->multi_cmds, ' '); // Add all whitespaces
		(*list) = (*list)->next;
	}
	*list = tmp;
}

void	minihell_entrance(t_hell *mini)
{
	t_env	*lst;
	t_list	*list;
	char	*line;
	int		i;
	int		x;

	lst = NULL;
	list = NULL;
	line = NULL;
	i = 0;
	x = 1;
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
			line = add_whitespaces(mini);
			split_and_store(line, &list);
			split_and_store2(&list);
			if (is_heredoc(list))
				open_and_heredoc(&list);
			else if (is_append(list))
				open_and_append(&list);
			else if (is_output(list))
				open_and_output(&list);
			else if (is_input(list))
				open_and_input(&list);
			choose_and_acquire(mini, lst, list);
			// while (list)
			// {
			// 	while (list->command[i])
			// 	{
			// 		printf("Command = %s\n", list->command[i]);
			// 		i++;
			// 	}
			// 	i = 0;
			// 	list = list->next;
			// }
			ft_lstclear(&list);
		}
	}
}
