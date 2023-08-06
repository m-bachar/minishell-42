/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:16:28 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/06 17:51:28 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_and_output(char *str1, char *str2, t_list *list)
{
	char		*file_name;

	file_name = NULL;
	if (!ft_strcmp(str1, ">"))
	{
		if (list->file_out > 2)
			close(list->file_out);
		file_name = ft_strdup(str2);
		list->file_out = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (list->file_out == -1)
			return (free(file_name), 1);
		free(file_name);
	}
	return (0);
}
