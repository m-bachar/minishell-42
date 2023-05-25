/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:20:26 by mbachar           #+#    #+#             */
/*   Updated: 2023/05/25 01:25:04 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	red(void)
{
	printf("\033[1;31m");
}

void	green(void)
{
	printf("\033[1;32m");
}

void	reset(void)
{
	printf("\033[0m");
}

void	ft_errors(char *str)
{
	red();
	printf("Error\t: ");
	reset();
	printf("%s !\n", str);
	exit (1);
}
