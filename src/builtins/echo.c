/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:47:21 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/27 02:51:07 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo(t_list *list)
{
	int	index;
	int	flag;

	index = 1;
	flag = 0;
	if (!list->command)
		return ;
	if (list->command[0] && !list->command[1])
	{
		printf("\n");
		return ;
	}
	while (list->command[index] && !check_n(list->command[index]))
	{
		index++;
		flag = 1;
	}
	while (list->command[index])
	{
		printf("%s", list->command[index++]);
		if (list->command[index] != NULL)
			printf(" ");
	}
	if (!flag)
		printf("\n");
}

int	check_n(char *str)
{
	int	index;

	index = 1;
	if (!str[index])
		return (1);
	while (str[index])
	{
		if (str[index] != 'n')
			return (1);
		index++;
	}
	return (0);
}
