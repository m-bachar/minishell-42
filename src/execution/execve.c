/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:44:18 by otchekai          #+#    #+#             */
/*   Updated: 2023/08/05 18:16:46 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_path(t_hell *mini, t_env *lst, t_list *split)
{
	int		i;
	char	*slash;

	if (split->command[0][0] == '/' || split->command[0][0] == '.')
	{
		mini->to_find = split->command[0];
		return ;
	}
	slash = "/";
	i = 0;
	while (lst)
	{
		if (!ft_strncmp(lst->env_name, "PATH", 5))
			mini->path = ft_split(lst->env_value, ':');
		lst = lst->next;
	}
	while (mini->path[i++])
		mini->path[i] = ft_strjoin(mini->path[i], slash);
	i = -1;
	while (mini->path[++i])
	{
		mini->to_find = ft_strjoin(mini->path[i], split->command[0]);
		if (!access(mini->to_find, F_OK | X_OK))
			break ;
	}
}

void	one_command(t_hell *mini, t_env **lst, t_list *list)
{
	int	i;
	int	fok;

	i = 0;
	if (!pipe_check(mini))
	{
		if (choose_and_acquire(mini, lst, list) == 1)
			return ;
	}
	fok = fork();
	if (fok == 0)
	{
		if ((choose_and_acquire(mini, lst, list)) == 1 && pipe_check(mini) == 1)
			exit (1);
		if (list->file_out != 1)
			dup2(list->file_out, 1);
		if (list->file_in != 0)
			dup2(list->file_in, 0);
		check_path(mini, *lst, list);
		if (execve(mini->to_find, list->command, 
				convert_to_2d_array(*lst)) == -1)
			ft_putstr_fd("command not found", 2);
		exit(1);
	}
}

void    commands(t_list *list, t_hell *mini, t_env **lst)
{
	int		fok;
	int		in;
	int		out;
	t_list	*tmp;
	int		fd[2];

	in = dup(0);
	out = dup(1);
	tmp = list;
	while (tmp->next)
	{
		pipe(fd);
		fok = fork();
		if (fok == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (list->file_out != 1)
				dup2(list->file_out, 1);
			if (list->file_in != 0)
				dup2(list->file_in, 0);
			if ((choose_and_acquire(mini, lst, tmp)) == 1)
				exit (1);
			check_path(mini, *lst, tmp);
			if (execve(mini->to_find, tmp->command,
					convert_to_2d_array(*lst)) == -1)
				ft_putstr_fd("command not found", 2);
			exit(1);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		tmp = tmp->next;
	}
	signal(SIGQUIT, ctrl_that_thing);
	one_command(mini, lst, tmp);
	dup2(out, 1);
	dup2(in, 0);
	while (wait(NULL) != -1);
}

int	pipe_check(t_hell *mini)
{
	int	index;

	index = 0;
	while (mini->line[index])
	{
		if (mini->line[index] == '|')
			return (1);
		index++;
	}
	return (0);
}
