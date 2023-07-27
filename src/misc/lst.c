/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:04:05 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/27 14:24:54 by mbachar          ###   ########.fr       */
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

t_list	*ft_lstnew(char *data)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->multi_cmds = ft_strdup(data);
	node->command = NULL;
	node->file_in = 0;
	node->file_out = 1;
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
