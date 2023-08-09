/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:04:09 by otchekai          #+#    #+#             */
/*   Updated: 2023/08/09 14:53:00 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	choose_and_acquire(t_hell *mini, t_env **lst, t_list *list)
{
	if (list->command[0] && !ft_strncmp(list->command[0], "pwd", 4))
		return (print_current_directory(mini, *lst), 1);
	else if (list->command[0] && !ft_strncmp(list->command[0], "echo", 5))
		return (echo(list), 1);
	else if (list->command[0] && !ft_strncmp(list->command[0], "unset", 6))
		return (unset(lst, list, mini), 1);
	else if (list->command[0] && !ft_strncmp(list->command[0], "cd", 3))
		return (update_pwds(*lst, list, mini), 1);
	else if (list->command[0] && !ft_strncmp(list->command[0], "export", 7) && \
		list->command[1])
		return (ft_export(lst, mini, list), 1);
	else if (list->command[0] && !strncmp(list->command[0], "env", 4))
		return (print_env(*lst), 1);
	else if (list->command[0] && !ft_strncmp(list->command[0], "export", 7))
		return (print_export(*lst), 1);
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

void	convert_norminette(t_env *env_list, t_hell *mini)
{
	int		i;
	t_env	*current;

	i = 0;
	mini->count = 0;
	current = env_list;
	while (current != NULL)
	{
		mini->count++;
		current = current->next;
	}
}

char	**convert_to_2d_array(t_env *env_list, t_hell *mini)
{
	t_env	*current;
	char	**array;
	char	*to_fill;
	int		i;

	convert_norminette(env_list, mini);
	i = 0;
	current = env_list;
	array = malloc((mini->count + 1) * sizeof(char *));
	while (current != NULL)
	{
		mini->name_length = ft_strlen(current->env_name);
		mini->value_length = ft_strlen(current->env_value);
		mini->total_length = mini->name_length + mini->value_length + 2;
		array[i] = malloc(mini->total_length * sizeof(char));
		to_fill = array[i];
		joint_it(&to_fill, current);
		current = current->next;
		i++;
	}
	array[mini->count] = NULL;
	return (array);
}

int	export_key(char *str)
{
	if (!ft_strcmp(str, ""))
	{
		printf("Empty Key!!\n");
		return (1);
	}
	return (0);
}
