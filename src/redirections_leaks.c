/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_leaks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:41:29 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/06 17:22:34 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		get_size_double_char(char **arr)
{
	int		i = 0;

	while(arr[i])
		i++;
	return(i);
}

int	remove_NUL(t_list **mini)
{
	t_list	*lst;
	char	**arr;
	int		i;
	int		j;

	lst = *mini;
	while (lst)
	{
		i = 0;
		j = 0;
		arr = ft_calloc(get_size_double_char(lst->command) + 1, sizeof(char **));
		if (!arr)
			return (1);
		while (lst->command[i])
		{
			if (ft_strcmp(lst->command[i], "NUL") != 0)
				arr[j++] = ft_strdup(lst->command[i++]);
			else
				i++;
		}
		free_mem(lst->command);
		lst->command = arr;
		lst = lst->next;
	}
	return (0);
}

void	remove_args_from_redirections(t_list **mini)
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
			if (!ft_strcmp((*mini)->command[i], "<<") || !ft_strcmp((*mini)->command[i], "<")
				|| !ft_strcmp((*mini)->command[i], ">>") || !ft_strcmp((*mini)->command[i], ">"))
			{
				free((*mini)->command[i]);
				(*mini)->command[i] = ft_strdup("NUL");
				free((*mini)->command[i + 1]);
				(*mini)->command[i + 1] = ft_strdup("NUL");
			}
			i++;
		}
		(*mini) = (*mini)->next;
	}
	*mini = tmp;
}
