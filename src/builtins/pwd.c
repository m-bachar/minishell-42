/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:21:15 by otchekai          #+#    #+#             */
<<<<<<< HEAD:src/builtins/pwd.c
/*   Updated: 2023/06/22 13:04:34 by otchekai         ###   ########.fr       */
=======
/*   Updated: 2023/06/30 16:35:57 by mbachar          ###   ########.fr       */
>>>>>>> main:src/builtings/pwd.c
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
<<<<<<< HEAD:src/builtins/pwd.c
	printf("%s\n", mini->pwd);
=======
	printf("%s\n", cmd);
>>>>>>> main:src/builtings/pwd.c
}
