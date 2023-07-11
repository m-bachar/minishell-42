/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:44:18 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/11 20:16:11 by otchekai         ###   ########.fr       */
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

void	one_command(t_hell *mini, t_env *lst, t_list *split)
{
	t_env	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	if (!tmp)
		return ;
	check_path(mini, lst, split);
	execve(mini->to_find, split->command, convert_to_2d_array(tmp));
	exit(1);
	while (wait(NULL) != -1);
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
			check_path(mini, lst, tmp);
			execve(mini->to_find, tmp->command, convert_to_2d_array(lst));
			exit(1);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		tmp = tmp->next;
	}
	dup2(out, 1);
	fok = fork();
	if (fok == 0)
		one_command(mini, lst, tmp);
	dup2(in, 0);
	while (wait(NULL) != -1);
}
