/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:18:25 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/03 13:18:32 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*copy_env(t_env *lst, char **envs)
{
	char	env_name[MAX_SIZE];
	char	env_value[MAX_SIZE];
	char	*env_name_heap;
	char	*env_value_heap;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (envs[j])
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
		while (envs[j][i])
		{
			env_value[k] = envs[j][i];
			k++;
			i++;
		}
		env_value[k] = '\0';
		env_name_heap = malloc(sizeof(char) * ft_strlen(env_name) + 1);
		env_value_heap = malloc(sizeof(char) * ft_strlen(env_value) + 1);
		if (!env_name_heap || !env_value_heap)
			return (free(env_name_heap), free(env_value_heap), NULL);
		ft_lstadd_back1(&lst, ft_lstnew1(ft_strcpy(env_name_heap, env_name),
				ft_strcpy(env_value_heap, env_value)));
		i = 0;
		k = 0;
		j++;
	}
	return (free(env_name_heap), free(env_value_heap), lst);
}
