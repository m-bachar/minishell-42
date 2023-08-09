/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:01:18 by otchekai          #+#    #+#             */
/*   Updated: 2023/08/09 14:57:33 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_check(t_hell *mini)
{
	int	i;

	i = -1;
	while (mini->new_key[++i])
	{
		if ((!i && !ft_isalpha(mini->new_key[i])) || \
			(i && !ft_isalnum(mini->new_key[i])))
		{
			printf("Forbidden key!\n");
			return (1);
		}
	}
	return (0);
}

int	export_first(t_hell *mini, char *str)
{
	int		i;

	i = 0;
	if (!str || !*str || !mini)
		return (1);
	while ((str[i] && str[i] != '='))
		i++;
	if (i > 0 && str[i - 1] == '+')
	{
		mini->join_val = 1;
		str[i - 1] = '\0';
		mini->new_val = ft_strdup(&str[i + 1]);
	}
	else if (str[i] == '=')
	{
		str[i] = '\0';
		mini->new_val = ft_strdup(&str[i + 1]);
	}
	else if (str[i] == '\0') 
		mini->new_val = NULL;
	mini->new_key = ft_strdup(str);
	if (export_check(mini) || export_key(str))
		return (1);
	return (0);
}

void	update_env(t_env *lst, t_hell *mini)
{
	while (lst)
	{
		if (lst->env_name && mini->new_key && \
			!ft_strcmp(lst->env_name, mini->new_key))
		{
			if (mini->join_val == 1)
			{
				lst->env_value = ft_strjoin(lst->env_value, \
				ft_strdup(mini->new_val));
			}
			else if (!mini->new_val && lst->env_value != NULL)
			{
				mini->expo_var = 1;
				break ;
			}
			else
			{
				free(lst->env_value);
				lst->env_value = ft_strdup(mini->new_val);
			}
			mini->expo_var = 1;
			break ;
		}
		lst = lst->next;
	}
}

void	ft_export(t_env **lst, t_hell *mini, t_list *list)
{
	t_env	*tmp;
	int		i;

	i = 1;
	tmp = *lst;
	mini->expo_var = 0;
	while (list->command[i])
	{
		mini->join_val = 0;
		if (export_first(mini, list->command[i]))
			return ;
		update_env(tmp, mini);
		if (!mini->expo_var)
			ft_lstadd_back1(lst, ft_lstnew1(mini->new_key, mini->new_val));
		i++;
	}
}

void	print_export(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->env_value)
			printf("declare -x %s=%s\n", tmp->env_name, tmp->env_value);
		else
			printf("declare -x %s\n", tmp->env_name);
		tmp = tmp->next;
	}
}
