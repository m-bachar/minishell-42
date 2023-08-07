/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:16:30 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/07 14:39:08 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_flag;

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

char	*del_name(char *del)
{
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	name = ft_calloc(MAX_SIZE, 1);
	while (del[i])
	{
		if (del[i] == '\'' || del[i] == '\"')
		{
			i++;
			while (del[i] && del[i] != '\'' && del[i] != '\"')
			{
				name[j] = del[i];
				j++;
				i++;
			}
			break ;
		}
	}
	return (name);
}

int	open_and_heredoc(t_list **mini, t_env **env)
{
	t_list	*tmp;
	char	*line;
	char	*random;
	int		file_id;
	int		i;

	tmp = *mini;
	i = 0;
	while ((*mini) != NULL)
	{
		while ((*mini)->command[i])
		{
			random = NULL;
			line = NULL;
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
				if ((*mini)->command[i][0] != '\'' && (*mini)->command[i][0] != '\"')
					line = expand_in_heredoc(line, env);
				else
					(*mini)->command[i] = del_name((*mini)->command[i]);
				ft_putstr_fd(line, file_id);
				while (ft_strcmp2(line, (*mini)->command[i]))
				{
					if (line)
						free(line);
					line = readline("😃 Heredoc > ");
					if ((*mini)->command[i][0] != '\'' && (*mini)->command[i][0] != '\"')
						line = expand_in_heredoc(line, env);
					else
						(*mini)->command[i] = del_name((*mini)->command[i]);
					if (!ft_strcmp2(line, (*mini)->command[i]))
						break ;
					ft_putstr_fd(line, file_id);
				}
				if (return_input(file_id, random))
					return (1);
				close(file_id);
				file_id = open(random, O_RDONLY);
				(*mini)->file_in = file_id;
			}
			free(line);
			free(random);
			i++;
		}
		i = 0;
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
	return (0);
}
