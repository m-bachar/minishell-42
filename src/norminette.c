/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:04:09 by otchekai          #+#    #+#             */
/*   Updated: 2023/08/05 18:19:54 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	choose_and_acquire(t_hell *mini, t_env **lst, t_list *list)
{
	if (list->command[0] && !ft_strncmp(list->command[0], "pwd", 4))
		return (print_current_directory(mini), 1);
	else if (list->command[0] && !ft_strncmp(list->command[0], "echo", 5))
		return (echo(list), 1);
	else if (list->command[0] && !ft_strncmp(list->command[0], "unset", 6))
		return (unset(lst, list), 1);
	else if (list->command[0] && !ft_strncmp(list->command[0], "cd", 3))
		return (update_pwds(*lst, list), 1);
	else if (list->command[0] && !ft_strncmp(list->command[0], "export", 7) && \
		list->command[1])
		return (ft_export(*lst, mini, list), 1);
	else if (list->command[0] && !strncmp(list->command[0], "env", 4))
		return (print_env(*lst), 1);
	else if (list->command[0] && !ft_strncmp(list->command[0], "export", 7))
		return (print_export(*lst, list), 1);
	else if (list->command[0] && !ft_strncmp(list->command[0], "exit", 5))
		return (exit_hell(list->command + 1), 1);
	return (0);
}

void	joint_it(char **s, t_env *env)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (env->env_name[i])
		(*s)[k++] = env->env_name[i++];
	(*s)[k++] = '=';
	i = 0;
	while (env->env_value[i])
		(*s)[k++] = env->env_value[i++];
	(*s)[k] = '\0';
}

char	**convert_to_2d_array(t_env *env_list)
{
	int		count;
	int		i;
	t_env	*current;
	char	**array;
	char	*to_fill;

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
		to_fill = array[i];
		joint_it(&to_fill, current);
		current = current->next;
		i++;
	}
	array[count] = NULL;
	return (array);
}
