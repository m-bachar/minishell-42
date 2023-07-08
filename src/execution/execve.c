/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:44:18 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/08 11:06:49 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execution(t_hell *mini, t_env *lst)
{
	t_env *tmp;
	int	i;
	char **env;
	char *to_find = NULL;

	char **cmds = ft_split(mini->line, ' ');
	char *slash = "/";
	env = mini->vne;
	tmp = lst;
	i = 0;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env_name, "PATH", 4))
		{
			mini->path = ft_split(tmp->env_value, ':');
		}
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (mini->path[i])
	{
		mini->path[i] = ft_strjoin(mini->path[i], slash);
		i++;
	}
	i = 0;
	while (mini->path[i])
	{
		to_find = ft_strjoin(mini->path[i], cmds[0]);
		if (!access(to_find, F_OK | X_OK))
			break ;
		i++;
	}
	int j = fork();
	if (j == 0)
	{
		execve(to_find, cmds, env);
		printf(RED"%s : cmd not found\n"RESET, cmds[0]);
		exit (1);
	}
	while (wait(NULL) != -1);
}
