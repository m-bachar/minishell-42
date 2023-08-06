/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:16:30 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/06 17:54:18 by mbachar          ###   ########.fr       */
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
		ioctl(0,TIOCSTI, "\4");
		return ;
	}
}

int	return_input(int file_id, char *random)
{
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
	random = NULL;
	line = NULL;
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
				{
					write(2, "ERROR\n", 7);
					break ;
				}
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
				close(file_id);
				if (return_input(file_id, random))
					return (1);
				file_id = open(random, O_RDONLY);
				(*mini)->file_in = file_id;
			}
			i++;
		}
		i = 0;
		(*mini) = (*mini)->next;
	}
	free(line);
	free(random);
	*mini = tmp;
	return(0);
}
