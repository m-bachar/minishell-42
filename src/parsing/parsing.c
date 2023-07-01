/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:18:25 by mbachar           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/07 22:31:10 by otchekai         ###   ########.fr       */
=======
/*   Updated: 2023/06/30 16:35:38 by mbachar          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_env(t_env **lst, char **envs)
{
	char	env_name[MAX_SIZE];
	char	env_value[MAX_SIZE];
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (envs[j])
	{
		i = 0;
		while (envs[j][i] != '=')
		{
			env_name[k] = envs[j][i];
			k++;
			i++;
		}
		env_name[k] = '\0';
		k = 0;
		i++;
		while (envs[j][i])
		{
			env_value[k] = envs[j][i];
			k++;
			i++;
		}
		env_value[k] = '\0';
		ft_lstadd_back1(lst, ft_lstnew1(env_name, env_value));
		i = 0;
		k = 0;
		j++;
	}
}
