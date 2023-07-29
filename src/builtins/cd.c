/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 00:40:28 by otchekai          #+#    #+#             */
/*   Updated: 2023/07/29 22:24:48 by otchekai         ###   ########.fr       */
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

void	update_pwds(t_env *lst, t_list *list)
{
	char	*old_pwd;
	char	*current_pwd;
	t_env	*tmp;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return ;
	change_directory(list, lst);
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

void	change_directory(t_list *list, t_env *lst)
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
	if (chdir(list->command[1]) == -1)
		return ;
}
