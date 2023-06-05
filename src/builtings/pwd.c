/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:21:15 by otchekai          #+#    #+#             */
/*   Updated: 2023/06/04 22:21:37 by otchekai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_current_directory(void)
{
	char	*cmd;

	cmd = getcwd(NULL, 0);
	if (cmd == NULL)
	{
		printf("pwd Error\n");
		exit(1);
	}
	printf("%s\n", cmd);
}