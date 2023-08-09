/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:21:15 by otchekai          #+#    #+#             */
/*   Updated: 2023/08/09 14:58:21 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_current_directory(t_hell *mini, t_env *lst)
{
	t_env	*tmp;
	char	*store;

	tmp = lst;
	mini->pwd = getcwd(NULL, 0);
	store = NULL;
	if (!mini->pwd)
	{
		tmp = check_env(lst, "PWD");
		printf("%s\n", tmp->env_value);
		mini->exit_status = 1;
		return ;
	}
	printf("%s\n", mini->pwd);
	mini->exit_status = 0;
	free(mini->pwd);
}
