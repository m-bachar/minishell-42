/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:32:31 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/05 17:07:15 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_var_value_heredoc(t_env **env, char *env_name)
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

char	*extract_var_name_heredoc(char *data)
{
	char	varname[MAX_SIZE];
	char	*envname;
	int		i;
	int		j;

	i = 0;
	j = 0;
	envname = NULL;
	i++;
	while (data[i] && ft_isalnum(data[i]))
	{
		varname[j] = data[i];
		i++;
		j++;
	}
	varname[j] = '\0';
	envname = ft_strdup(varname);
	return (envname);
}

char	*expand_in_heredoc(char *line, t_env **env)
{
	int		i;
	char	*varname;
	char	*varvalue;

	i = 0;
	varname = NULL;
	varvalue = NULL;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$')
		{
			varname = extract_var_name_heredoc(line);
			varvalue = extract_var_value_heredoc(env, varname);
		}
		i++;
	}
	if (!varvalue)
		return (free(varname), line);
	return (free(varname), varvalue);
}
