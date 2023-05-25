/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:14:19 by mbachar           #+#    #+#             */
/*   Updated: 2022/11/10 00:05:38 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	c;
	char	endline;

	i = 0;
	endline = '\n';
	if (s == 0)
		return ;
	while (s[i] != 0)
	{
		c = s[i];
		write(fd, &c, 1);
		i++;
	}
	write(fd, &endline, 1);
}
