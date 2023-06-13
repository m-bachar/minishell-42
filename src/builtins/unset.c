/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:17:23 by otchekai          #+#    #+#             */
/*   Updated: 2023/06/13 13:29:28 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset(t_env **lst, t_hell *mini)
{
	t_env	*tmp;
	t_env	*temp;
	t_env	*purpose;
	int		index;

	index = 1;
	while (mini->splitted[index])
	{
		tmp = *lst;
		temp = *lst;
		if (tmp->env_name && !strcmp(mini->splitted[index], tmp->env_name))
			*lst = tmp->next;
		while (tmp)
		{
			if (tmp->env_name && !strcmp(mini->splitted[index], tmp->env_name))
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
		index++;
	}
}
