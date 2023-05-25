/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:25:27 by mbachar           #+#    #+#             */
/*   Updated: 2023/05/24 03:18:38 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *env[])
{
	t_hell	mini;

	(void)av;
	(void)env;
	if (ac == 1)
	{
		minihell_entrance(&mini);
	}
	else
		ft_errors("Too many arguments");
}
