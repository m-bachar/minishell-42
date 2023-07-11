/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:04:09 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/11 16:41:51 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	choose_and_acquire(t_hell *mini, t_env *lst, t_list *split)
{
	t_env	*tmp;

	tmp = lst;
	if (!ft_strncmp(split->command[0], "pwd", 4))
	{
		if (split->command[1])
			print_current_directory(mini);
		else
			print_current_directory(mini);
	}
	else if (!ft_strncmp(split->command[0], "export", 7) && \
		split->command[1])
		ft_export(lst, mini);
	else if (!ft_strncmp(split->command[0], "cd", 3))
		update_pwds(lst, split);
	else if (!ft_strncmp(split->command[0], "echo", 5))
		echo(split);
	else if (mini->line && !strncmp(mini->line, "env", 4))
		print_env(tmp);
	else if (mini->line && !ft_strncmp(mini->line, "export", 7))
		print_export(tmp, mini);
	else
		commands(split, mini, lst);
}

char	**convert_to_2d_array(t_env *env_list)
{
	int		count;
	int		i;
	t_env	*current;
	char	**array;

	i = 0;
	count = 0;
	current = env_list;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	array = malloc((count + 1) * sizeof(char *));
	current = env_list;
	while (current != NULL)
	{
		int name_length = strlen(current->env_name);
		int value_length = strlen(current->env_value);
		int total_length = name_length + value_length + 2;
		array[i] = malloc(total_length * sizeof(char));
		current = current->next;
		i++;
	}
	array[count] = NULL;
	return (array);
}
