/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:32:19 by slimane           #+#    #+#             */
/*   Updated: 2025/07/26 12:29:36 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *str, int fd)
{
	if (fd < 0)
		return ;
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

int	ft_parse_char(char *str)
{
	int		i;
	char	*trim;
	int		count;

	i = 0;
	if (!str)
		return (-1);
	trim = ft_strtrim(str, " \n");
	if (!trim)
		return (-1);
	count = 0;
	while (trim && trim[i])
	{
		if (trim[i] != ',' && ft_isdigit(trim[i]) == 0 && trim[i] != ' ')
			return (free(trim), ft_putendl_fd("ERROR an !digit found in the hex number", 2), -1);
		if (trim[i] == ',')
			count++;
		if (count > 2 )
			return (free(trim), ft_putendl_fd("ERROR alot of , in F or C check it", 2), -1);
		i++;
	}
	return (free(trim), 0);
}

long	ft_create_color(int r, int g, int b)
{
	return ((r << 16) + (g << 8) + b);
}

int	count_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_valid_nb(char *str)
{
	int		i;
	char	*trim;
	i = 0;

	trim = ft_strtrim(str, " ");
	if (!trim)
		return (1);
	while (trim[i])
	{
		if (ft_isdigit(trim[i]) == 0)
			return (free(trim), 1);
		i++;
	}
	return (free(trim), 0);
}

int	ft_convert_hex(char *str)
{
	int		i;
	char	**split;
	int		red;
	int		green;
	int		blue;
	long	color;

	i = 0;
	if (ft_parse_char(str) != 0)
		return (-1);
	split = ft_split(str, ',');
	if (split == NULL || count_split(split) != 3)
		return (ft_putendl_fd("ERROR FROM SPLIT OR YOU ENTER MORE THAN OR LESS\
			3 colors(r,g,b)", 2), -1);
	red = ft_atoi(split[0]);
	if (red > 255 || ft_valid_nb(split[0]))
		return (ft_putendl_fd("ERROR red color is > 255 or have ' '", 2), ft_free(split, -1), free(str), -1);
	green = ft_atoi(split[1]);
	if (green > 255 || ft_valid_nb(split[1]))
		return (ft_putendl_fd("ERROR green color is > 255 or have ' '", 2), ft_free(split, -1), free(str), -1);
	blue = ft_atoi(split[2]);
	if (blue > 255 || ft_valid_nb(split[2]))
		return (ft_putendl_fd("ERROR blue color is > 255 or have ' '", 2), ft_free(split, -1), free(str), -1);
	color = ft_create_color(red, green, blue);
	return (ft_free(split, -1), free(str), color);
}
