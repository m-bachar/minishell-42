/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:47:21 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/07 20:48:40 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo(t_hell *mini)
{
	int	index;
	int	flag;

	index = 1;
	flag = 0;
	if (!mini->splitted)
		return ;
	if (mini->splitted[0] && !mini->splitted[1])
	{
		printf("\n");
		return ;
	}
	while (mini->splitted[index] && !check_n(mini->splitted[index]))
	{
		index++;
		flag = 1;
	}
	while (mini->splitted[index])
	{
		printf("%s", mini->splitted[index++]);
		if (mini->splitted[index] != NULL)
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
