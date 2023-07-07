/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:16:28 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/07 16:12:27 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_and_output(t_list **mini)
{
	t_list	*tmp;
	char	*file_name;
	int		file_id;

	tmp = *mini;
	while ((*mini) != NULL)
	{
		if ((*mini)->token == FILE_OUT)
		{
			if (file_id > 2)
				close(file_id);
			file_name = ft_strdup((*mini)->next->data);
			file_id = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
		}
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
	free(file_name);
	return (file_id);
}
