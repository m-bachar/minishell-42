/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:17:23 by otchekai          #+#    #+#             */
/*   Updated: 2023/06/24 00:22:10 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_key(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if ((!i && !ft_isalpha(str[i])) || \
			(i && !ft_isalnum(str[i])))
			printf("Forbidden key!\n");
	}
	return ;
}

void	unset(t_env **lst, t_hell *mini)
{
	t_env	*tmp;
	t_env	*temp;
	t_env	*purpose;
	int		index;

	index = 1;
	check_key(mini->splitted[index]);
	while (mini->splitted[index])
	{
		tmp = *lst;
		temp = *lst;
		if (tmp && !strcmp(mini->splitted[index], tmp->env_name))
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
