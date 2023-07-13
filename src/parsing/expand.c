/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:07:28 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/12 23:35:32 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_var_name(t_list **mini)
{
	t_list	*tmp;
	char	*var;
	int		i;
	int		j;
	int		k;

	tmp = *mini;
	i = 0;
	j = 0;
	k = 0;
	var = malloc(sizeof(char) * MAX_SIZE);
	if (!var)
		return (NULL);
	while (*mini)
	{
		while ((*mini)->command[j])
		{
			while ((*mini)->command[j][i])
			{
				if ((*mini)->command[j][i] == '$')
				{
					i++;
					while ((*mini)->command[j][i] && ft_isalnum((*mini)->command[j][i]))
					{
						var[k] = (*mini)->command[j][i];
						k++;
						i++;
					}
					var[k] = '\0';
				}
				else
					i++;
			}
			i = 0;
			j++;
		}
		(*mini) = (*mini)->next;
	}
	(*mini) = tmp;
	return (var);
}

char	*extract_var_value(t_env **env, char *env_name)
{
	t_env	*tmp;
	char	*env_value;
	int		i;

	tmp = (*env);
	i = 0;
	env_value = NULL;
	while ((*env))
	{
		if (!ft_strcmp((*env)->env_name, env_name))
		{
			env_value = ft_strdup((*env)->env_value);
			break ;
		}
		(*env) = (*env)->next;
	}
	(*env) = tmp;
	return (env_value);
}
