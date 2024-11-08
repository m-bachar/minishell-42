/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_store.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:35:36 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/05 20:16:42 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_and_store2(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (*list)
	{
		(*list)->command = ft_split2((*list)->multi_cmds, " \t\r\n\v\f");
		(*list) = (*list)->next;
	}
	*list = tmp;
}

void	split_and_store(char *line, t_list **mini)
{
	char	**splitted;
	int		i;

	i = 0;
	splitted = ft_split(line, '|');
	if (splitted == NULL || splitted[0] == NULL)
		return ;
	while (splitted[i])
	{
		ft_lstadd_back(mini, ft_lstnew(splitted[i]));
		i++;
	}
	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}
