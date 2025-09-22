/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_help_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:40:16 by slimane           #+#    #+#             */
/*   Updated: 2025/09/14 11:35:03 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *str, int fd)
{
	if (fd < 0)
		return ;
	if (fd == 2)
		ft_putstr_fd("ERROR: ", fd);
	if (str)
	{
		ft_putstr_fd(str, fd);
		write(fd, "\n", 1);
	}
}

int	ft_isdigit(int c)
{
	if (c <= 57 && c >= 48)
		return (1);
	return (0);
}
