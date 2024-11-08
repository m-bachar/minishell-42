/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 05:28:30 by mbachar           #+#    #+#             */
/*   Updated: 2023/07/07 17:55:41 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int		i;
	char	c;

	i = 0;
	if (s == 0)
		return ;
	while (s[i] != '\0')
	{
		c = s[i];
		write(fd, &c, 1);
		i++;
	}
	ft_putchar_fd('\n', fd);
}
