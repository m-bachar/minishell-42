/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:17:23 by otchekai          #+#    #+#             */
/*   Updated: 2023/08/05 18:13:48 by mbachar          ###   ########.fr       */
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

void	unset(t_env **lst, t_list *list)
{
	t_env	*tmp;
	t_env	*temp;
	t_env	*purpose;
	int		index;

	index = 1;
	check_key(list->command[index]);
	while (list->command[index])
	{
		tmp = *lst;
		temp = *lst;
		if (tmp && !ft_strcmp(list->command[index], tmp->env_name))
			*lst = (*lst)->next;
		while (tmp)
		{
			if (tmp->env_name && !ft_strcmp(list->command[index], 
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
		index++;
	}
}
