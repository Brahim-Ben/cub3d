/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:32:19 by slimane           #+#    #+#             */
/*   Updated: 2025/09/20 17:35:56 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
			return (free(trim), trim = NULL, ft_putendl_fd(
					"an !digit or digit < 0 found in the hex number", 2), -1);
		if (trim[i] == ',')
			count++;
		if (count > 2)
			return (free(trim), trim = NULL, ft_putendl_fd(
					"alot of ',' in F or C check it", 2), -1);
		i++;
	}
	return (free(trim), trim = NULL, 0);
}

long	ft_create_color(int r, int g, int b)
{
	return ((r << 16) + (g << 8) + b);
}

int	count_split(char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_just_space(str[i]) == 0)
			count++;
		i++;
	}
	return (count);
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
			return (free(trim), trim = NULL, 1);
		i++;
	}
	return (free(trim), trim = NULL, 0);
}

int	ft_convert_hex(char *str)
{
	char	**split;
	int		red;
	int		green;
	int		blue;

	if (ft_parse_char(str) != 0)
		return (free(str), -1);
	split = ft_split(str, ',');
	if (split == NULL || count_split(split) != 3)
		return (ft_putendl_fd("FROM SPLIT OR > or < 3 r,g,b", 2), free(str),
			ft_free(split, -1), -1);
	red = ft_atoi(split[0]);
	if (red > 255 || ft_valid_nb(split[0]))
		return (ft_putendl_fd("red color is > 255 or have ' '", 2),
			ft_free(split, -1), free(str), str = NULL, -1);
	green = ft_atoi(split[1]);
	if (green > 255 || ft_valid_nb(split[1]))
		return (ft_putendl_fd("green color is > 255 or have ' '", 2),
			ft_free(split, -1), free(str), str = NULL, -1);
	blue = ft_atoi(split[2]);
	if (blue > 255 || ft_valid_nb(split[2]))
		return (ft_putendl_fd("blue color is > 255 or have ' '", 2),
			ft_free(split, -1), free(str), str = NULL, -1);
	return (ft_free(split, -1), free(str), ft_create_color(red, green, blue));
}
