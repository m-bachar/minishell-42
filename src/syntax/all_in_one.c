/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_in_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 01:23:15 by mbachar           #+#    #+#             */
/*   Updated: 2023/05/26 05:06:41 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	all_begining_syntaxes(t_hell *mini)
{
	if (!append_begining(mini) || !heredoc_begining(mini)
		|| !pipe_begining(mini) || !file_in_begining(mini)
		|| !file_out_begining(mini))
		return (0);
	return (1);
}

int	all_middle_syntaxes(t_hell *mini)
{
	if (!quotes(mini))
		return (0);
	if (!append_middle(mini) || !heredoc_middle(mini)
		|| !pipe_middle(mini) || !file_in_middle(mini)
		|| !file_out_middle(mini))
		return (0);
	return (1);
}

int	all_ending_syntaxes(t_hell *mini)
{
	if (!append_ending(mini) || !heredoc_ending(mini)
		|| !pipe_ending(mini) || !file_in_ending(mini)
		|| !file_out_ending(mini))
		return (0);
	return (1);
}
