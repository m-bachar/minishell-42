/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:42:52 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/04 23:20:40 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	quotes(t_hell *mini)
{
	int	flag_single_quotes;
	int	flag_double_quotes;
	int	i;

	flag_single_quotes = 0;
	flag_double_quotes = 0;
	i = 0;
	while (mini->line[i])
	{
		if (mini->line[i] == '"')
		{
			flag_double_quotes++;
			i++;
			while (mini->line[i] && mini->line[i] != '"')
				i++;
			if (mini->line[i])
				flag_double_quotes++;
		}
		else if (mini->line[i] == '\'')
		{
			flag_single_quotes++;
			i++;
			while (mini->line[i] && mini->line[i] != '\'')
				i++;
			if (mini->line[i])
				flag_single_quotes++;
		}
		if (!mini->line[i])
			break;
		i++;
	}
	if (flag_double_quotes % 2 == 0 && flag_single_quotes % 2 == 0)
		return (1);
	return (0);
}
