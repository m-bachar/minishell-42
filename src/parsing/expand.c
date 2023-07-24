/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:07:28 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/25 00:28:39 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		if (!strcmp((*env)->env_name, env_name))
		{
			env_value = ft_strdup((*env)->env_value);
			break ;
		}
		(*env) = (*env)->next;
	}
	(*env) = tmp;
	return (env_value);
}

void	skip_or_replace(t_list	**mini, t_env **env)
{
	t_list	*tmp;
	int		i;
	int		j;
	int		k;
	int		l;
	char	str[MAX_SIZE];
	char	*var_value;
	char	var_name[MAX_SIZE];

	var_value = NULL;
	tmp = *mini;
	while ((*mini))
	{
		j = 0;
		while ((*mini)->command[j])
		{
			i = 0;
			l = 0;
			k = 0;
			if ((*mini)->command[j][i] == '\"')
			{
				i++;
				while ((*mini)->command[j][i] && (*mini)->command[j][i] != '\"')
				{
					if ((*mini)->command[j][i] == '$')
					{
						i++;
						while ((*mini)->command[j][i] && ft_isalnum((*mini)->command[j][i]))
						{
							var_name[l] = (*mini)->command[j][i];
							i++;
							l++;
						}
						var_name[l] = '\0';
						var_value = extract_var_value(env, var_name);
						// printf("Var Name = %s\tVar Value = %s\n", var_name, var_value);
						l = 0;
						if (var_value != NULL)
						{
							while (var_value[l])
							{
								str[k] = var_value[l];
								l++;
								k++;
							}
						}
					}
					else
					{
						str[k] = (*mini)->command[j][i];
						k++;
						i++;
					}
				}
				str[k] = '\0';
				(*mini)->command[j] = str;
				printf("command[%d] = %s\n", 0, (*mini)->command[0]);
				printf("command[%d] = %s\n", 1, (*mini)->command[1]);
				printf("command[%d] = %s\n", 2, (*mini)->command[2]);
			}
			j++;
		}
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
}
