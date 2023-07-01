/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:44:18 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/01 16:44:36 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execution(t_hell *mini)
{
	int	i;
	char **env;
	char *to_find = NULL;

	char **cmds = ft_split(mini->line, ' ');
	char *slash = "/";
	env = mini->vne;
	i = 0;
	if (!ft_strncmp(mini->line, "pwd", 4))
		return ;
	while (mini->vne[i])
	{
		if (!ft_strncmp(mini->vne[i], "PATH=", 5))
			mini->path = ft_split(mini->vne[i] + 5, ':');
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
		printf("ZABI\n");
	}
	while (wait(NULL) != -1);
}