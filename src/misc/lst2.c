/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 02:24:37 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/27 02:26:07 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstadd_back1(t_env **lst, t_env *new)
{
	t_env	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

t_env	*ft_lstnew1(char *env_name, char *env_value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (free(node), NULL);
	node->env_name = ft_strdup(env_name);
	node->env_value = ft_strdup(env_value);
	node->next = NULL;
	return (node);
}

int	ft_lstsize1(t_env *lst)
{
	t_env	*ptr;
	int		i;

	i = 0;
	if (lst == NULL)
		return (0);
	ptr = lst;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}
