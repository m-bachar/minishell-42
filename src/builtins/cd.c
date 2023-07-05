/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 00:40:28 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/05 16:56:49 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*check_env(t_env *lst, char *str)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!strcmp(tmp->env_name, str))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void	update_pwds(t_env *lst, t_hell *mini)
{
	char	*old_pwd;
	char	*current_pwd;
	t_env	*tmp;


	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return ;
	change_directory(mini, lst);
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return ;
	tmp = check_env(lst, "OLDPWD");
	if (!tmp)
		return ;
	free(tmp->env_value);
	tmp->env_value = old_pwd;
	tmp = check_env(lst, "PWD");
	if (!tmp)
		return ;
	free(tmp->env_value);
	tmp->env_value = current_pwd;
}

void	change_directory(t_hell *mini, t_env *lst)
{
	int		i;
	t_env	*tmp;

	i = 0;

	if (!mini->splitted[1] || !ft_strncmp(mini->splitted[1], "~", 2))
	{
		tmp = check_env(lst, "HOME");
		if (!tmp)
			return ;
		chdir(tmp->env_value);
	}
	if (chdir(mini->splitted[1]) == -1)
		return ;
}
