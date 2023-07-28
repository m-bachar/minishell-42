/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:07:28 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/28 16:42:39 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_var_value(t_env **env, char *env_name)
{
	t_env	*tmp;
	char	*env_value;

	tmp = (*env);
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

void	extract_var_name(char *data, char **returned_var,
		t_hell *mini, t_env **env)
{
	char	varname[MAX_SIZE];
	char	*varvalue;
	int		k;

	k = 0;
	mini->i++;
	while (data[mini->i] && ft_isalnum(data[mini->i]))
	{
		varname[k] = data[mini->i];
		mini->i++;
		k++;
	}
	varname[k] = '\0';
	varvalue = extract_var_value(env, varname);
	if (varvalue)
	{
		k = 0;
		while (varvalue[k])
			(*returned_var)[mini->j++] = varvalue[k++];
		free(varvalue);
		varvalue = NULL;
	}
}

char	*expand_or_skip(char *str, t_hell *mini, t_env **env)
{
	char	final_var[MAX_SIZE];
	char	*var;

	mini->i = 0;
	mini->j = 0;
	while (str[mini->i])
	{
		if (str[mini->i] == '\'')
		{
			mini->i++;
			while (str[mini->i] && str[mini->i] != '\'')
			{
				final_var[mini->j] = str[mini->i];
				mini->i++;
				mini->j++;
			}
			mini->i++;
		}
		else if (str[mini->i] == '\"')
		{
			mini->i++;
			while (str[mini->i] && str[mini->i] != '\"')
			{
				if (str[mini->i] == '$')
				{
					var = final_var;
					extract_var_name(str, &var, mini, env);
				}
				else
				{
					final_var[mini->j] = str[mini->i];
					mini->i++;
					mini->j++;
				}
			}
			mini->i++;
		}
		else if (str[mini->i] == '$')
		{
			var = final_var;
			extract_var_name(str, &var, mini, env);
		}
		else if (str[mini->i])
		{
			final_var[mini->j] = str[mini->i];
			mini->i++;
			mini->j++;
		}
	}
	final_var[mini->j] = '\0';
	return (ft_strdup(final_var));
}

void	skip_or_replace(t_list	**mini, t_env **env, t_hell *hell)
{
	t_list	*tmp;
	char	*new_value;
	int		j;

	tmp = *mini;
	new_value = NULL;
	while ((*mini))
	{
		j = 0;
		while ((*mini)->command[j])
		{
			new_value = expand_or_skip((*mini)->command[j],
					hell, env);
			free((*mini)->command[j]);
			(*mini)->command[j] = new_value;
			j++;
		}
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
}
