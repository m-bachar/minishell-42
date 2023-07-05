/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:44:18 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/05 17:15:07 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execution(t_hell *mini, t_env *lst)
{
	t_env	*tmp;
	int		i;
	char	**env;
	char	*to_find;
	char	*slash;

	to_find = NULL;
	env = mini->vne;
	tmp = lst;
	i = 0;
	slash = "/";
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
		to_find = ft_strjoin(mini->path[i], mini->splitted[0]);
		if (!access(to_find, F_OK | X_OK))
			break ;
		i++;
	}
	i = fork();
	if (i == 0)
	{
		execve(to_find, mini->splitted, env);
		printf(RED"%s : cmd not found\n"RESET, mini->splitted[0]);
	}
	while (wait(NULL) != -1);
}
