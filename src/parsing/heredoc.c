/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:16:30 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/07 20:00:51 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*rand_name(void)
{
	static size_t	i;
	char			*number;
	char			*name;

	number = ft_itoa(i);
	name = ft_strjoin("./tmp/tmp_", number);
	i++;
	return (free(number), name);
}

int	open_and_heredoc(t_list **mini)
{
	t_list	*tmp;
	char	*line;
	int		file_id;

	tmp = *mini;
	while ((*mini) != NULL)
	{
		if ((*mini)->token == HEREDOC)
		{
			(*mini) = (*mini)->next;
			file_id = open(rand_name(), O_CREAT | O_RDWR | O_TRUNC, 0777);
			line = readline("😃 Heredoc > ");
			while (line && ft_strcmp(line, (*mini)->data))
			{
				ft_putstr_fd(line, file_id);
				free(line);
				line = readline("😃 Heredoc > ");
			}
		}
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
	return (file_id);
}
