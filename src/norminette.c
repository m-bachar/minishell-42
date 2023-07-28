/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:04:09 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/28 16:58:12 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	choose_and_acquire(t_hell *mini, t_env *lst, t_list *list)
{
	t_env	*tmp;

	tmp = lst;
	if (list->command[0] && !ft_strncmp(list->command[0], "pwd", 4))
	{
		print_current_directory(mini);
		return (1);
	}
	else if (list->command[0] && !ft_strncmp(list->command[0], "echo", 5))
	{
		echo(list);
		return (1);
	}
	else if (list->command[0] && !ft_strncmp(list->command[0], "unset", 6))
	{
		unset(&tmp, list);
		return (1);
	}
	else if (list->command[0] && !ft_strncmp(list->command[0], "cd", 3))
	{
		update_pwds(tmp, list);
		return (1);
	}
	else if (list->command[0] && !ft_strncmp(list->command[0], "export", 7) && \
		list->command[1])
	{
		ft_export(tmp, mini, list);
		return (1);
	}
	else if (list->command[0] && !strncmp(list->command[0], "env", 4))
	{
		print_env(tmp);
		return (1);
	}
	else if (list->command[0] && !ft_strncmp(list->command[0], "export", 7))
	{
		print_export(tmp, list);
		return (1);
	}
	return (0);
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
		int name_length = ft_strlen(current->env_name);
		int value_length = ft_strlen(current->env_value);
		int total_length = name_length + value_length + 2;
		array[i] = malloc(total_length * sizeof(char));
		current = current->next;
		i++;
	}
	array[count] = NULL;
	return (array);
}
