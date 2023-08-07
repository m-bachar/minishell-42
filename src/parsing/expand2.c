/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:07:03 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/07 17:08:50 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	single_quotes2(t_hell *mini, char *final_var, char *str)
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

void	double_quotes2(t_hell *mini, char *final_var, char *str, t_env **env)
{
	mini->i++;
	while (str[mini->i] && str[mini->i] != '\"')
	{
		if (str[mini->i] == '$' && iswhitespace(str[mini->i + 1]))
		{
			final_var[mini->j] = str[mini->i];
			mini->i++;
			mini->j++;
		}
		else if (str[mini->i] == '$')
		{
			mini->var = final_var;
			extract_var_name(str, &mini->var, mini, env);
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
