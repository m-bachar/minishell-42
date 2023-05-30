/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:18:25 by mbachar           #+#    #+#             */
/*   Updated: 2023/05/28 22:56:49 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parsing(t_list *mini)
{
	t_list	*head;

	head = mini;
	while (mini != NULL)
	{
		printf("id = %d\tdata = %s\n", mini->id, mini->data);
		mini = mini->next;
	}
	return (0);
}

void	copy_env(t_env *lst, char **envs)
{
	char	env_name[1000];
	char	env_value[1000];
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (envs[j][i])
	{
		if (i == 0)
		{
			while (envs[j][i] != '=')
			{
				env_name[k] = envs[j][i];
				k++;
				i++;
			}
			env_name[k] = '\0';
			k = 0;
			i++;
		}
		else
		{
			while (envs[j][i])
			{
				env_value[k] = envs[j][i];
				k++;
				i++;
			}
			env_value[k] = '\0';
			ft_lstadd_back1(&lst, ft_lstnew1(env_name, env_value));
			i = 0;
			k = 0;
		}
		j++;
	}
}
