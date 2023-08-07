/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 22:31:10 by otchekai          #+#    #+#             */
/*   Updated: 2023/08/07 17:27:40 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_env(t_env **lst, char **envs)
{
	char	env_name[MAX_SIZE];
	char	env_value[MAX_SIZE];
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (envs[j])
	{
		k = 0;
		i = 0;
		while (envs[j][i] != '=')
			env_name[k++] = envs[j][i++];
		env_name[k] = '\0';
		k = 0;
		i++;
		while (envs[j][i])
			env_value[k++] = envs[j][i++];
		env_value[k] = '\0';
		ft_lstadd_back1(lst, ft_lstnew1(env_name, env_value));
		j++;
	}
}

void	print_env(t_env *lst)
{
	while (lst)
	{
		if (lst->env_value && !ft_strncmp(lst->env_value, "", 1))
		{
			lst = lst->next;
			continue ;
		}
		printf("%s=%s\n", lst->env_name, lst->env_value);
		lst = lst->next;
	}
}
