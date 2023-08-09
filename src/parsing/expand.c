/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:07:28 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/08 23:52:46 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	get_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**assign_2d_to_2d(char *varvalue)
{
	char	**splitted;
	char	**returned;
	int		i;

	i = 0;
	splitted = ft_split2(varvalue, " \t\r\n\v\f");
	varvalue = NULL;
	returned = malloc(sizeof(char **) * (get_size(splitted) + 1));
	if (!returned)
		return (NULL);
	while (splitted[i])
	{
		returned[i] = ft_strdup(splitted[i]);
		i++;
	}
	returned[i] = NULL;
	free_mem(splitted);
	return (returned);
}

int	iswhitespaces2(char *s, char *c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] != c[j] && s[i] && c[j])
			j++;
		if (iswhitespace(c[j]))
			return (1);
		j = 0;
		i++;
	}
	return (0);
}

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
	if (iswhitespaces2(varvalue, " \t\r\n\v\f") && varvalue)
		mini->expanded = assign_2d_to_2d(varvalue);
	else if (varvalue)
	{
		k = 0;
		while (varvalue[k])
			(*returned_var)[mini->j++] = varvalue[k++];
		if (varvalue)
			free(varvalue);
		varvalue = NULL;
	}
}

char	*expand_or_skip(char *str, t_hell *mini, t_env **env)
{
	char	*final_var;

	mini->i = 0;
	mini->j = 0;
	final_var = ft_calloc(MAX_SIZE, sizeof(char));
	while (str[mini->i])
	{
		if (str[mini->i] == '\'')
			single_quotes2(mini, final_var, str);
		else if (str[mini->i] == '\"')
			double_quotes2(mini, final_var, str, env);
		else if (str[mini->i] == '$')
		{
			mini->var = final_var;
			extract_var_name(str, &mini->var, mini, env);
		}
		else if (str[mini->i])
			final_var[mini->j++] = str[mini->i++];
	}
	return (final_var);
}

char	**ft_strdup2(char **str)
{
	char	**new;
	int		i;
	
	i = 0;

	new = malloc(sizeof(char **) * (get_size(str) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[i] = ft_strdup(str[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
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
			if (!ft_strcmp("awk", (*mini)->command[j]))
				j += 2;
			new_value = expand_or_skip((*mini)->command[j],
					hell, env);
			free((*mini)->command[j]);
			(*mini)->command[j] = ft_strdup(new_value);
			j++;
		}
		if (hell->expanded)
			(*mini)->command = ft_strdup2(hell->expanded);
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
}
