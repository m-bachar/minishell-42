/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:16:30 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/28 14:46:23 by mbachar          ###   ########.fr       */
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
	static size_t	flag;
	int				access_flag;
	char			*number;
	char			*name;

	access_flag = 0;
	number = ft_itoa(i);
	name = ft_strjoin(ft_strdup("./tmp/tmp_"), number);
	access_flag = access(name, F_OK);
	while (!access_flag && flag++ <= SIZE_T_MAX)
	{
		i = flag;
		free(name);
		name = NULL;
		if (number)
			free(number);
		number = ft_itoa(i);
		if (name)
			free(name);
		name = ft_strjoin(ft_strdup("./tmp/tmp_"), number);
		access_flag = access(name, F_OK);
	}
	return (free(number), name);
}

// void    ft_signal_handler2(int sig)
// {
//     if (sig == SIGINT)
//     {
//         g_flag = 1;
//         close(0);
//         return ;
//     }
// }

void	open_and_heredoc(t_list **mini) // CTRL+C ==> quits minishell - CTRL+D ==> SEGV
{
	t_list	*tmp;
	char	*line;
	char	*random;
	int		file_id;
	int		i;

	tmp = *mini;
	i = 0;
	random = NULL;
	while ((*mini) != NULL)
	{
		while ((*mini)->command[i])
		{
			if (!ft_strcmp((*mini)->command[i], "<<"))
			{
				i++;
				if (random)
					free(random);
				random = rand_name();
				file_id = open(random, O_CREAT | O_RDWR | O_TRUNC, 0777);
				// ft_signal_handler2();
				line = readline("😃 Heredoc > ");
				ft_putstr_fd(line, file_id);
				while (ft_strcmp(line, (*mini)->command[i]))
				{
					if (line)
						free(line);
					line = readline("😃 Heredoc > ");
					if (!ft_strcmp(line, (*mini)->command[i]))
						break ;
					ft_putstr_fd(line, file_id);
					(*mini)->file_in = file_id;
				}
			}
			i++;
		}
		i = 0;
		(*mini) = (*mini)->next;
	}
	free(line);
	free(random);
	*mini = tmp;
}
