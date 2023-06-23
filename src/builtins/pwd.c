/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:21:15 by otchekai          #+#    #+#             */
/*   Updated: 2023/06/22 13:04:34 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_current_directory(t_hell *mini)
{
	mini->pwd = getcwd(NULL, 0);
	if (mini->pwd == NULL)
	{
		printf("pwd Error\n");
		exit(1);
	}
	printf("%s\n", mini->pwd);
}
