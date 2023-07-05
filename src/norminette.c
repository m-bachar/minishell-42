/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:04:09 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/05 17:15:11 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	choose_and_acquire(t_hell *mini, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	if (!ft_strncmp(mini->splitted[0], "pwd", 4))
	{
		if (mini->splitted[1])
			print_current_directory(mini);
		else
			print_current_directory(mini);
	}
	else if (!ft_strncmp(mini->splitted[0], "export", 7)
		&& mini->splitted[1])
		ft_export(lst, mini);
	else if (!ft_strncmp(mini->splitted[0], "cd", 3))
		update_pwds(lst, mini);
	else if (!ft_strncmp(mini->splitted[0], "unset", 6))
		unset(&lst, mini);
	else if (!ft_strncmp(mini->splitted[0], "echo", 5))
		echo(mini);
	else if (mini->line && !strncmp(mini->line, "env", 4))
		print_env(tmp);
	else if (mini->line && !ft_strncmp(mini->line, "export", 7))
		print_export(tmp, mini);
	else
		execution(mini, lst);
}
