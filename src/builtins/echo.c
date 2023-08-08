/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:47:21 by otchekai          #+#    #+#             */
/*   Updated: 2023/08/08 20:58:46 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo_putstr_fd(char *s, int fd)
{
	int		i;
	char	c;

	i = 0;
	if (s == 0)
		return ;
	while (s[i] != '\0')
	{
		c = s[i];
		write(fd, &c, 1);
		i++;
	}
}

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
		echo_putstr_fd("\n", 1);
		return ;
	}
	while (list->command[index] && !check_n(list->command[index]))
	{
		index++;
		flag = 1;
	}
	while (list->command[index])
	{
		echo_putstr_fd(list->command[index++], 1);
		if (list->command[index] != NULL)
			echo_putstr_fd(" ", 1);
	}
	if (!flag)
		echo_putstr_fd("\n", 1);
}

int	check_n(char *str)
{
	int	index;

	index = 1;
	if (!str || !str[0])
		return (1);
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
