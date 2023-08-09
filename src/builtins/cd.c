/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 00:40:28 by otchekai          #+#    #+#             */
/*   Updated: 2023/08/09 12:49:09 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*check_env(t_env *lst, char *str)
{
	while (lst)
	{
		if (!ft_strcmp(lst->env_name, str))
			return (lst);
		lst = lst->next;
	}
	return (0);
}

void	update_pwds(t_env *lst, t_list *list, t_hell *mini)
{
	char	*old_pwd;
	char	*current_pwd;
	t_env	*tmp;

	old_pwd = getcwd(NULL, 0);
	change_directory(list, lst, mini);
	current_pwd = getcwd(NULL, 0);
	tmp = check_env(lst, "OLDPWD");
	if (!tmp)
		return ;
	if (old_pwd)
	{
		free(tmp->env_value);
		tmp->env_value = old_pwd;
	}
	tmp = check_env(lst, "PWD");
	if (!tmp)
		return ;
	if (current_pwd)
	{
		free(tmp->env_value);
		tmp->env_value = current_pwd;
	}
}

void	change_directory(t_list *list, t_env *lst, t_hell *mini)
{
	int		i;

	i = 0;
	if (!list->command[1] || !ft_strncmp(list->command[1], "~", 2))
	{
		lst = check_env(lst, "HOME");
		if (!lst)
			return ;
		chdir(lst->env_value);
	}
	else if (chdir(list->command[1]) == -1)
	{
		ft_putstr_fd("cd: No such file or directory", 2);
		mini->exit_status = 1;
		return ;
	}
}
