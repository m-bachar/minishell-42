/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:53:05 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/08 22:39:55 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_append(t_list *mini)
{
	int	i;

	i = 0;
	while (mini != NULL)
	{
		while (mini->command[i])
		{
			if (!ft_strcmp(mini->command[i], ">>"))
				return(1);
			i++;
		}
		i = 0;
		mini = mini->next;
	}
	return (0);
}

void	open_and_append(t_list **mini)
{
	t_list	*tmp;
	char	*file_name;
	int		file_id;
	int		i;

	tmp = *mini;
	i = 0;
	while ((*mini) != NULL)
	{
		while ((*mini)->command[i])
		{
			if (!ft_strcmp((*mini)->command[i], ">>"))
			{
				if (file_id > 2)
					close(file_id);
				file_name = ft_strdup((*mini)->command[i + 1]);
				file_id = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
				(*mini)->file_out = file_id;
			}
			i++;
		}
		i = 0;
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
	// free(file_name);
}
