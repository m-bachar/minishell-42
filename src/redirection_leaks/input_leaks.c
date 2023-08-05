/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_leaks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:41:07 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/05 16:52:07 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	single_arg_input(t_list **mini, int i)
{
	t_list	*tmp;

	tmp = *mini;
	free((*mini)->command[i]);
	(*mini)->command[i] = NULL;
	free((*mini)->command[i + 1]);
	(*mini)->command[i + 1] = NULL;
	*mini = tmp;
}

void	multiple_args_input(t_list **mini, int i, int j)
{
	t_list	*tmp;

	tmp = *mini;
	j = i + 2;
	while ((*mini)->command[j])
	{
		if (!ft_strcmp((*mini)->command[j], "<"))
		{
			free((*mini)->command[j]);
			(*mini)->command[j] = NULL;
			free((*mini)->command[j + 1]);
			(*mini)->command[j + 1] = NULL;
			j += 2;
		}
		else
		{
			free((*mini)->command[i]);
			(*mini)->command[i] = NULL;
			free((*mini)->command[i + 1]);
			(*mini)->command[i + 1] = NULL;
			(*mini)->command[i] = ft_strdup((*mini)->command[j]);
			i++;
			j++;
		}
	}
	free((*mini)->command[i]);
	(*mini)->command[i] = NULL;
	free((*mini)->command[i + 1]);
	(*mini)->command[i + 1] = NULL;
	*mini = tmp;
}

void	remove_args_from_input(t_list **mini)
{
	t_list	*tmp;
	int		i;
	int		j;

	tmp = *mini;
	i = 0;
	j = 0;
	while (*mini)
	{
		while ((*mini)->command[i])
		{
			if (!ft_strcmp((*mini)->command[i], "<"))
			{
				if ((*mini)->command[i + 2] == NULL)
					single_arg_input(mini, i);
				else
					multiple_args_input(mini, i, j);
			}
			i++;
		}
		i = 0;
		j = 0;
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
}