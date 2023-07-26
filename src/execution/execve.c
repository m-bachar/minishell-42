/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benito <benito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:44:18 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/25 10:51:37 by benito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_path(t_hell *mini, t_env *lst, t_list *split)
{
	int		i;
	t_env	*tmp;
	char	*slash;

	tmp = lst;
	slash = "/";
	i = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env_name, "PATH", 5))
			mini->path = ft_split(tmp->env_value, ':');
		tmp = tmp->next;
	}
	while (mini->path[i++])
		mini->path[i] = ft_strjoin(mini->path[i], slash);
	i = 0;
	while (mini->path[i])
	{
		mini->to_find = ft_strjoin(mini->path[i], split->command[0]);
		if (!access(mini->to_find, F_OK | X_OK))
			break ;
		i++;
	}
}

void	one_command(t_hell *mini, t_env *lst, t_list *list)
{
	t_env	*tmp;
	int		fok;

	tmp = lst;
	if (!tmp)
		return ;
	if ((choose_and_acquire(mini, tmp, list)) == 1)
		return ;
	fok = fork();
	if (fok == 0)
	{
		check_path(mini, tmp, list);
		if (execve(mini->to_find, list->command, convert_to_2d_array(tmp)) == -1)
			ft_putstr_fd("command not found", 2);
		exit(1);
	}
}

void	commands(t_list *list, t_hell *mini, t_env *lst)
{
	int			fok;
	int			in;
	int			out;
	t_list		*tmp;
	int			fd[2];

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
			choose_and_acquire(mini, lst, tmp);
			check_path(mini, lst, tmp);
			if (execve(mini->to_find, tmp->command,
					convert_to_2d_array(lst)) == -1)
				ft_putstr_fd("command not found", 2);
			exit(1);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		tmp = tmp->next;
	}
	dup2(out, 1);
	one_command(mini, lst, tmp);
	dup2(in, 0);
	while (wait(NULL) != -1);
}
