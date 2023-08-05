/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:16:28 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/05 16:45:12 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_output(t_list *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mini != NULL)
	{
		while (mini->command[j])
		{
			if (mini->command[j][i] == '>' && mini->command[j][i + 1] == '\0')
				return (1);
			j++;
		}
		j = 0;
		mini = mini->next;
	}
	return (0);
}

void	open_and_output(t_list **mini)
{
	t_list		*tmp;
	char		*file_name;
	static int	file_id;
	int			i;

	tmp = *mini;
	file_name = NULL;
	while ((*mini) != NULL)
	{
		i = 0;
		while ((*mini)->command[i])
		{
			if (!ft_strcmp((*mini)->command[i], ">"))
			{
				if (file_id > 2)
					close(file_id);
				file_name = ft_strdup((*mini)->command[i + 1]);
				file_id = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
				if (file_id == -1)
				{
					free(file_name);
					remove_args_from_output(mini);
					(*mini)->file_out = file_id;
					return ;
				}
				free(file_name);
				(*mini)->file_out = file_id;
			}
			i++;
		}
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
	remove_args_from_output(mini);
}
