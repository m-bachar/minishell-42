/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:43:45 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/28 16:08:13 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ctrl_c(int sig)
{
	int	status;

	(void)sig;
	if (waitpid(-1, &status, WNOHANG) == 0)
		return ;
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrl_that_thing(int sig)
{
	(void)sig;
	printf("Quit : 3\n");
}