/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:53:05 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/07 16:12:24 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_and_append(t_list **mini)
{
	t_list	*tmp;
	char	*file_name;
	int		file_id;

	tmp = *mini;
	while ((*mini) != NULL)
	{
		if ((*mini)->token == APPEND)
		{
			if (file_id > 2)
				close(file_id);
			file_name = ft_strdup((*mini)->next->data);
			file_id = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
		}
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
	free(file_name);
	return (file_id);
}
