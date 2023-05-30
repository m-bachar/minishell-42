/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:04:05 by mbachar           #+#    #+#             */
/*   Updated: 2023/05/30 11:19:11 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

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

t_list	*ft_lstnew(char *data, int id, int token)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->data = data;
	node->id = id;
	node->token = token;
	node->next = NULL;
	return (node);
}

int	ft_lstsize(t_list *lst)
{
	t_list	*ptr;
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

// t_env
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
		return (NULL);
	node->env_name = env_name;
	node->env_value = env_value;
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
