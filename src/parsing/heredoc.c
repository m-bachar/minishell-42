/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:16:30 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/08 22:48:23 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_heredoc(t_list *mini)
{
	int	i;

	i = 0;
	while (mini != NULL)
	{
		while (mini->command[i])
		{
			if (!ft_strcmp(mini->command[i], "<<"))
				return(1);
			i++;
		}
		i = 0;
		mini = mini->next;
	}
	return (0);
}

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

void	open_and_heredoc(t_list **mini)
{
	t_list	*tmp;
	char	*line;
	int		file_id;
	int		i;

	tmp = *mini;
	i = 0;
	while ((*mini) != NULL)
	{
		while ((*mini)->command[i])
		{
			if (!ft_strcmp((*mini)->command[i], "<<"))
			{
				i++;
				file_id = open(rand_name(), O_CREAT | O_RDWR | O_TRUNC, 0777);
				line = readline("😃 Heredoc > ");
				while (line && ft_strcmp(line, (*mini)->command[i]))
				{
					ft_putstr_fd(line, file_id);
					free(line);
					line = NULL;
					line = readline("😃 Heredoc > ");
					(*mini)->file_in = file_id;
				}
			}
			i++;
		}
		i = 0;
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
	// free((*mini));
}
