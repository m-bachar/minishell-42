/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:16:30 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/12 19:01:48 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_heredoc(t_list *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mini != NULL)
	{
		while (mini->command[j])
		{
			if (mini->command[j][i] == '<' && mini->command[j][i + 1] == '<')
				return (1);
			j++;
		}
		j = 0;
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
				file_id = open(rand_name(), O_CREAT | O_RDWR | O_TRUNC, 0777); // Check if file exists
				line = readline("😃 Heredoc > ");
				while (ft_strcmp2(line, (*mini)->command[i]))
				{
					ft_putstr_fd(line, file_id);
					free(line);
					line = NULL;
					line = readline("😃 Heredoc > ");
					ft_putstr_fd(line, file_id);
					(*mini)->file_in = file_id;
				}
				// Remove arg
			}
			i++;
		}
		i = 0;
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
	// free((*mini));
}
