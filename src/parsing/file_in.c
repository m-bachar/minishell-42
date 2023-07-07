/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:16:25 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/07 16:12:19 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_and_input(t_list **mini)
{
	t_list	*tmp;
	char	*file_name;
	int		file_id;

	tmp = *mini;
	while ((*mini) != NULL)
	{
		if ((*mini)->token == FILE_IN)
		{
			if (file_id > 2)
				close(file_id);
			file_name = ft_strdup((*mini)->next->data);
			file_id = open(file_name, O_RDONLY);
		}
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
	free(file_name);
	return (file_id);
}
