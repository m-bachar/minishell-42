/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:25:27 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/05 00:53:21 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *env[])
{
	t_hell	mini;

	(void)av;
	if (ac >= 1)
	{
		mini.vne = env;
		minihell_entrance(&mini);
	}
	else
		ft_errors("Too many arguments");
}
