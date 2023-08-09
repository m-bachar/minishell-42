/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:46:29 by otchekai          #+#    #+#             */
/*   Updated: 2023/08/09 16:53:29 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_check(t_hell *mini)
{
	int	index;

	index = 0;
	while (mini->line[index])
	{
		if (mini->line[index] == '|')
			return (1);
		index++;
	}
	return (0);
}

// void	commands_norminette(t_list *list, t_hell *mini, t_env **lst)
// {	
// 	mini->fork = fork();
// 	if (mini->fork == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		if (list->file_out != 1)
// 			dup2(list->file_out, 1);
// 		if (list->file_in != 0)
// 			dup2(list->file_in, 0);
// 		if ((choose_and_acquire(mini, lst, list)) == 1)
// 			exit (1);
// 		check_path(mini, *lst, list);
// 		if (!mini->to_find)
// 		{
// 			ft_putstr_fd("Command Not Found!!", 2);
// 			mini->exit_status = 127;
// 			exit (1);
// 		}
// 		if (execve(mini->to_find, list->command,
// 				convert_to_2d_array(*lst, mini)) == -1)
// 			return (printf("No Such File or Directory"),
// 				mini->exit_status = 1, exit(mini->exit_status));
// 		exit(1);
// 	}
// }
