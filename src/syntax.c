/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benito <benito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:29:00 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/01 13:14:27 by benito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minihell_entrance(t_hell *mini)
{
    t_env	*lst;
	t_env	*tmp;
	char	**split;
	int		i;
	int		j;

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
            || !all_middle_syntaxes(mini) || !all_ending_syntaxes(mini) || !quotes(mini))
            printf("😤 " RED "SyntaxError: " RESET
                "Oh dear! It appears you've encountered a syntax error.\n");
        add_history(mini->line);
        if (all_begining_syntaxes(mini)
            && all_middle_syntaxes(mini) && all_ending_syntaxes(mini) && quotes(mini))
        {
			line = add_whitespaces(mini);
			if (!ft_strncmp(mini->line, "pwd", 4))
				print_current_directory();
			split = ft_split(mini->line, ' ');
			if (!ft_strncmp(split[0], "export", 7) && split[1])
				ft_export(lst, mini);
		}
		execution(mini);
		tmp = lst;
		if (mini->line && !strncmp(mini->line, "env", 4))
		{
			while (tmp)
			{
				printf("%s=%s\n", tmp->env_name, tmp->env_value);
				tmp = tmp->next;
			}
			i = 0;
		}
	}
}
