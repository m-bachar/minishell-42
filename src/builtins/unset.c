/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:17:23 by otchekai          #+#    #+#             */
/*   Updated: 2023/08/09 15:18:24 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_key(char *str, t_hell *mini)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if ((!i && !ft_isalpha(str[i])) || \
			(i && !ft_isalnum(str[i])))
			printf("Forbidden key!\n");
		mini->exit_status = 1;
	}
	return ;
}

void	unset_norminette(t_env **lst, t_list *list, t_hell *mini)
{
	t_env	*tmp;
	t_env	*temp;
	t_env	*purpose;

	tmp = *lst;
	temp = *lst;
	if (tmp && !ft_strcmp(list->command[mini->unset_index], tmp->env_name))
		*lst = (*lst)->next;
	while (tmp)
	{
		if (tmp->env_name && !ft_strcmp(list->command[mini->unset_index], 
				tmp->env_name))
		{
			temp->next = tmp->next;
			purpose = tmp;
			tmp = tmp->next;
			free(purpose);
		}
		else
		{
			temp = tmp;
			tmp = tmp->next;
		}
	}
}

void	unset(t_env **lst, t_list *list, t_hell *mini)
{
	mini->unset_index = 1;
	check_key(list->command[mini->unset_index], mini);
	while (list->command[mini->unset_index])
	{
		unset_norminette(lst, list, mini);
		mini->unset_index++;
	}
}
