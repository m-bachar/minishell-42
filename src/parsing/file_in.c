/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:16:25 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/30 16:14:21 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_input(t_list *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mini != NULL)
	{
		while (mini->command[j])
		{
			if (mini->command[j][i] == '<' && mini->command[j][i + 1] == '\0')
				return (1);
			j++;
		}
		j = 0;
		mini = mini->next;
	}
	return (0);
}

int	open_and_input(t_list **mini)
{
	t_list		*tmp;
	char		*file_name;
	static int	file_id;
	int			i;

	tmp = *mini;
	while ((*mini) != NULL)
	{
		i = 0;
		while ((*mini)->command[i])
		{
			if (!ft_strcmp((*mini)->command[i], "<"))
			{
				if (file_id > 2)
					close(file_id);
				file_name = ft_strdup((*mini)->command[i + 1]);
				file_id = open(file_name, O_RDONLY);
				if (file_id == -1)
				{
					printf("😃 Minihell-1.0: %s: No such file or directory\n", file_name);
					free(file_name);
					remove_args_from_input(mini);
					(*mini)->file_in = file_id;
					return (0);
				}
				free(file_name);
				(*mini)->file_in = file_id;
			}
			i++;
		}
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
	remove_args_from_input(mini);
	return (1);
}

static void	single_arg(t_list **mini, int i)
{
	t_list	*tmp;

	tmp = *mini;
	free((*mini)->command[i]);
	(*mini)->command[i] = NULL;
	free((*mini)->command[i + 1]);
	(*mini)->command[i + 1] = NULL;
	*mini = tmp;
}

static void	multiple_args(t_list **mini, int i, int j)
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
	while (*mini)
	{
		i = 0;
		j = 0;
		while ((*mini)->command[i])
		{
			if (!ft_strcmp((*mini)->command[i], "<"))
			{
				if ((*mini)->command[i + 2] == NULL)
					single_arg(mini, i);
				else
					multiple_args(mini, i, j);
			}
			i++;
		}
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
}
