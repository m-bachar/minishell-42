/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:21:15 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/30 23:46:41 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_current_directory(t_hell *mini)
{
	mini->pwd = getcwd(NULL, 0);
	if (mini->pwd == NULL)
	{
		printf("pwd Error\n");
		return ;
	}
	printf("%s\n", mini->pwd);
	free(mini->pwd);
}
