/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:16:25 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/06 17:52:27 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_and_input(char *str1, char *str2, t_list *list)
{
	char		*file_name;

	file_name = NULL;
	if (!ft_strcmp(str1, "<"))
	{
		if (list->file_in > 2)
			close(list->file_in);
		file_name = ft_strdup(str2);
		list->file_in = open(file_name, O_RDONLY);
		if (list->file_in == -1)
		{
			printf("😃 Minihell-1.0: %s: No such file or directory\n", file_name);
			return (free(file_name), 1);
		}
		free(file_name);
	}
	return (0);
}
