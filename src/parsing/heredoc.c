/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:16:30 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/30 16:25:20 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_flag;

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

void	ft_signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		g_flag = 1;
		close(0);
		return ;
	}
}

int	return_input(int file_id, char *random)
{
	int	fd;

	fd = open(ttyname(1), O_RDONLY);
	if (fd == -1)
		return (perror("open"), free(random), 1);
	dup2(0, fd);
	if (g_flag == 1)
	{
		unlink(random);
		file_id = open(random, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (file_id < 0)
			return (perror("open"), free(random), 1);
		return (1);
	}
	return (0);
}

void	open_and_heredoc(t_list **mini)
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
			g_flag = 0;
			if (!ft_strcmp2((*mini)->command[i], "<<"))
			{
				i++;
				if (random)
					free(random);
				random = rand_name();
				signal (SIGINT, ft_signal_handler2);
				file_id = open(random, O_CREAT | O_RDWR | O_TRUNC, 0777);
				if (file_id == -1)
					write(2, "ERROR\n", 7);
				line = readline("😃 Heredoc > ");
				ft_putstr_fd(line, file_id);
				while (ft_strcmp2(line, (*mini)->command[i]))
				{
					if (line)
						free(line);
					line = readline("😃 Heredoc > ");
					if (!ft_strcmp2(line, (*mini)->command[i]))
						break ;
					ft_putstr_fd(line, file_id);
					(*mini)->file_in = file_id;
				}
				if (return_input(file_id, random))
					return ;
			}
			i++;
		}
		i = 0;
		(*mini) = (*mini)->next;
	}
	free(line);
	free(random);
	*mini = tmp;
	remove_args_from_heredoc(mini);
}

static void	single_arg(t_list **mini, int i)
{
	t_list	*tmp;

	tmp = *mini;
	free((*mini)->command[i]);
	(*mini)->command[i] = NULL;
	free((*mini)->command[i + 1]);
	(*mini)->command[i + 1] = NULL;
	*mini = tmp;
}

static void	multiple_args(t_list **mini, int i, int j)
{
	t_list	*tmp;

	tmp = *mini;
	j = i + 2;
	while ((*mini)->command[j])
	{
		if (!ft_strcmp((*mini)->command[j], "<<"))
		{
			free((*mini)->command[j]);
			(*mini)->command[j] = NULL;
			free((*mini)->command[j + 1]);
			(*mini)->command[j] = NULL;
			j += 2;
		}
		else
		{
			free((*mini)->command[i]);
			(*mini)->command[i] = NULL;
			free((*mini)->command[i + 1]);
			(*mini)->command[i + 1] = NULL;
			(*mini)->command[i] = ft_strdup((*mini)->command[j]);
			i++;
			j++;
		}
	}
	free((*mini)->command[i]);
	(*mini)->command[i] = NULL;
	free((*mini)->command[i + 1]);
	(*mini)->command[i] = NULL;
	*mini = tmp;
}

void	remove_args_from_heredoc(t_list **mini)
{
	t_list	*tmp;
	int		i;
	int		j;

	tmp = *mini;
	i = 0;
	j = 0;
	while (*mini)
	{
		while ((*mini)->command[i])
		{
			if (!ft_strcmp((*mini)->command[i], "<<"))
			{
				if ((*mini)->command[i + 2] == NULL)
					single_arg(mini, i);
				else
					multiple_args(mini, i, j);
			}
			i++;
		}
		i = 0;
		j = 0;
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
}
