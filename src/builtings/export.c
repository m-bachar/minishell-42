/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:01:18 by otchekai          #+#    #+#             */
/*   Updated: 2023/06/05 00:58:16 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void execution(t_hell *mini)
{
	int i;
	char **env = mini->vne;
	char *to_find = NULL;

	char **cmds = ft_split(mini->line, ' ');
	char *slash = "/";
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
		execve(to_find, cmds, env);
	while (wait(NULL) != -1);
}

int	export_first(t_hell *mini, char *str)
{
	int		i;

	i = 0;
	if (!str || !*str || !mini)
		return (1);
	while (str[i] && str[i] != '=')
		i++;
	if (i > 0 && str[i - 1] == '+')
	{
		mini->join_val = 1;
		str[i - 1] = '\0';
		mini->new_val = ft_strdup(&str[i + 1]);
	}
	else if (str[i] == '=')
	{
		str[i] = '\0';
		mini->new_val = ft_strdup(&str[i + 1]);
	}
	else if (str[i] == '\0')
		mini->new_val = ft_strdup("");
	mini->new_key = ft_strdup(str);
	i = -1;
	while (mini->new_key[++i])
	{
		if ((!i && !ft_isalpha(mini->new_key[i])) || \
			(i && !ft_isalnum(mini->new_key[i])))
		{
			printf("Forbidden key!\n");
			return (1);
		}
	}
	return (0);
}

void	ft_export(t_env *lst, t_hell *mini)
{
	t_env	*tmp;
	char	**split;
	int		var;
	int		i;

	i = 1;
	tmp = lst;
	split = ft_split(mini->line, ' ');
	while (split[i])
	{
		var = 0;
		mini->join_val = 0;
		if (export_first(mini, split[i]))
			return ;
		while (tmp)
		{
			if (tmp->env_name && mini->new_key && \
				!strcmp(tmp->env_name, mini->new_key))
			{
				if (mini->join_val == 1)
					tmp->env_value = ft_strjoin(tmp->env_value, \
					ft_strdup(mini->new_val));
				else
				{
					free(tmp->env_value);
					tmp->env_value = ft_strdup(mini->new_val);
				}
				var = 1;
				break ;
			}
			tmp = tmp->next;
		}
		if (!var)
			ft_lstadd_back1(&lst, ft_lstnew1(mini->new_key, mini->new_val));
		i++;
	}
}
