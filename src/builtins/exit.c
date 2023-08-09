/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:48:36 by otchekai          #+#    #+#             */
/*   Updated: 2023/08/09 13:58:06 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_exit(char *str)
{
	int	index;

	index = 0;
	if (str[index] == '-')
		index++;
	if (str[index] == '\0')
		return (1);
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (1);
		index++;
	}
	return (0);
}

void	exit_hell(char **str)
{
	int	index;
	int	var;

	index = 1;
	if (!str || !*str)
		exit (0);
	if (check_exit(str[0]) == 1 || ft_atoi(str[0]) > INT_MAX)
		exit (255);
	if (ft_atoi(str[0]) < 0)
		var = ft_atoi(str[0]) + 256;
	else
		var = ft_atoi(str[0]) % 256;
	exit (var);
}
