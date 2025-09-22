/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help_parse_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:16:25 by slimane           #+#    #+#             */
/*   Updated: 2025/09/18 14:34:07 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	ft_check_something_else(char *strs)
{
	char	**str;

	str = ft_split(strs, ' ');
	if (!str)
		return (ft_putendl_fd("from split", 2), 1);
	if (str[0] == NULL)
		return (ft_free(str, -1), 0);
	if (str[0] && ft_strcmp("NO", str[0]) == 0)
		return (ft_free(str, -1), 0);
	else if (str[0] && ft_strcmp("SO", str[0]) == 0)
		return (ft_free(str, -1), 0);
	else if (str[0] && ft_strcmp("WE", str[0]) == 0)
		return (ft_free(str, -1), 0);
	else if (str[0] && ft_strcmp("EA", str[0]) == 0)
		return (ft_free(str, -1), 0);
	else if (str[0] && ft_strcmp("F", str[0]) == 0)
		return (ft_free(str, -1), 0);
	else if (str[0] && ft_strcmp("C", str[0]) == 0)
		return (ft_free(str, -1), 0);
	else
	{
		ft_putstr_fd("INVALID KEY ", 2);
		return (ft_putendl_fd(str[0], 2), ft_free(str, -1), 1);
	}
	return (ft_free(str, -1), 0);
}

int	ft_mini_check(t_cub *cub, char *trim, int flag, int i)
{
	if (flag == 1)
	{
		if (cub->textures.north != NULL)
			return (ft_putendl_fd("NO already exits", 2), -1);
		cub->textures.north = ft_strtrim(&trim[i], " \n");
		if (!cub->textures.north || !ft_strcmp(cub->textures.north, "\0"))
			return (ft_putendl_fd("NO is NULL or empty", 2), -1);
	}
	else if (flag == 2)
	{
		if (cub->textures.south != NULL)
			return (ft_putendl_fd("SO already exits", 2), -1);
		cub->textures.south = ft_strtrim(&trim[i], " \n");
		if (!cub->textures.south || !ft_strcmp(cub->textures.south, "\0" ))
			return (ft_putendl_fd("SO is NULL or empty", 2), -1);
	}
	else if (flag == 3)
	{
		if (cub->textures.west != NULL)
			return (ft_putendl_fd("WE already exits", 2), -1);
		cub->textures.west = ft_strtrim(&trim[i], " \n");
		if (!cub->textures.west || !ft_strcmp(cub->textures.west, "\0"))
			return (ft_putendl_fd("WE is NULL or empty", 2), -1);
	}
	return (0);
}

int	ft__second_mini_check(t_cub *cub, char *trim, int flag, int i)
{
	if (flag == 4)
	{
		if (cub->textures.east != NULL)
			return (ft_putendl_fd("EA already exits", 2), -1);
		cub->textures.east = ft_strtrim(&trim[i], " \n");
		if (!cub->textures.east || !ft_strcmp(cub->textures.east, "\0"))
			return (ft_putendl_fd("EA is NULL or empty", 2), -1);
	}
	else if (flag == 5)
	{
		if (cub->colors.floor != -1)
			return (ft_putendl_fd("F duplicated", 2), -1);
		cub->colors.floor = ft_convert_hex(ft_strtrim(&trim[i], " \n"));
		if (cub->colors.floor == -1)
			return (-1);
	}
	else if (flag == 6)
	{
		if (cub->colors.ceiling != -1)
			return (ft_putendl_fd("C duplicated", 2), -1);
		cub->colors.ceiling = ft_convert_hex(ft_strtrim(&trim[i], " \n"));
		if (cub->colors.ceiling == -1)
			return (-1);
	}
	return (0);
}

int	check_min_textute(t_cub *cub, char *tmp, char *trim, int i)
{
	if (ft_strcmp(tmp, "NO") == 0)
	{
		if (ft_mini_check(cub, trim, 1, i) != 0)
			return (free(trim), free(tmp), -1);
		cub->config_count++;
	}
	else if (ft_strcmp(tmp, "SO") == 0)
	{
		if (ft_mini_check(cub, trim, 2, i) != 0)
			return (free(trim), free(tmp), -1);
		cub->config_count++;
	}
	else if (ft_strcmp(tmp, "WE") == 0)
	{
		if (ft_mini_check(cub, trim, 3, i) != 0)
			return (free(tmp), free(trim), -1);
		cub->config_count++;
	}
	else if (ft_strcmp(tmp, "EA") == 0)
	{
		if (ft__second_mini_check(cub, trim, 4, i) != 0)
			return (free(tmp), free(trim), -1);
		cub->config_count++;
	}
	return (0);
}

int	ft_check_colors(char *tmp, char *trim, t_cub *cub, int i)
{
	if (ft_strcmp(tmp, "F") == 0)
	{
		if (ft__second_mini_check(cub, trim, 5, i) != 0)
			return (free(trim), free(tmp), -1);
		cub->config_count++;
	}
	else if (ft_strcmp(tmp, "C") == 0)
	{
		if (ft__second_mini_check(cub, trim, 6, i) != 0)
			return (free(trim), free(tmp), -1);
		cub->config_count++;
	}
	return (0);
}
