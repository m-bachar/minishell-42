/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:29:00 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/13 13:23:11 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minihell_entrance(t_hell *mini)
{
	t_env	*lst;
	t_env	*tmp;
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
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
			if (!ft_strncmp(mini->splitted[0], "pwd", 4))
			{
				if (mini->splitted[1])
					print_current_directory(mini);
				else
					print_current_directory(mini);
			}
			if (!ft_strncmp(mini->splitted[0], "export", 7)
				&& mini->splitted[1])
				ft_export(lst, mini);
			if (!ft_strncmp(mini->splitted[0], "cd", 3))
				update_pwds(lst, mini);
			if (!ft_strncmp(mini->line, "ls", 3))
				execution(mini);
			if (!ft_strncmp(mini->splitted[0], "unset", 6))
				unset(&lst, mini);
		}
		tmp = lst;
		if (mini->line && !strncmp(mini->line, "env", 4))
		{
			while (tmp)
			{
				if (tmp->env_value && !ft_strncmp(tmp->env_value, "", 1))
				{
					tmp = tmp->next;
					continue ;
				}
				printf("%s=%s\n", tmp->env_name, tmp->env_value);
				tmp = tmp->next;
			}
		}
		if (mini->line && !ft_strncmp(mini->line, "export", 7))
		{
			while (tmp)
			{
				if (!ft_strncmp(tmp->env_value, "", 1))
					printf("%s%s\n", tmp->env_name, tmp->env_value);
				else
					printf("%s=%s\n", tmp->env_name, tmp->env_value);
				tmp = tmp->next;
			}
		}
	}
}
