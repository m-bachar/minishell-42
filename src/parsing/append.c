/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:53:05 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/07 17:55:33 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_and_append(char *str1, char *str2, t_list *list)
{
	char		*file_name;

	file_name = NULL;
	if (str1 && !ft_strcmp(str1, ">>"))
	{
		if (list->file_out > 2)
			close(list->file_out);
		file_name = ft_strdup(str2);
		list->file_out = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
		if (list->file_out == -1)
			return (free(file_name), 1);
		free(file_name);
	}
	return (0);
}
