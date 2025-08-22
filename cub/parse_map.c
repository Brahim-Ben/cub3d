/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:32:12 by slimane           #+#    #+#             */
/*   Updated: 2025/08/16 10:06:21 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_check_something_else(char *strs)
{
	char	**str;

	str = ft_split(strs, ' ');
	if (!str)
		return (ft_putendl_fd("error from split", 2), 1);
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
		ft_putstr_fd("ERROR INVALID KEY ", 2);
		return (ft_putendl_fd(str[0], 2), ft_free(str, -1), 1);
	}
	return (ft_free(str, -1), 0);
}

int	ft_mini_check(t_cub *cub, char *trim, int flag, int i)
{
	if (flag == 1)
	{
		if (cub->textures.north != NULL)
			return (ft_putendl_fd("Error NO already exits", 2), ft_free_texture(cub), -1);
		cub->textures.north = ft_strtrim(&trim[i], " \n");
		if (cub->textures.north == NULL || ft_strcmp(cub->textures.north, "\0") == 0)
			return (ft_putendl_fd("Error NO is NULL or empty", 2), ft_free_texture(cub), -1);
	}
	else if (flag == 2)
	{
		if (cub->textures.south != NULL)
			return (ft_putendl_fd("SO already exits", 2),ft_free_texture(cub),  -1);
		cub->textures.south = ft_strtrim(&trim[i], " \n");
		if (cub->textures.south == NULL || ft_strcmp(cub->textures.south, "\0" ) == 0)
			return (ft_putendl_fd("SO is NULL or empty", 2), ft_free_texture(cub), -1);
	}
	else if (flag == 3)
	{
		if (cub->textures.west != NULL)
			return (ft_putendl_fd("WE already exits", 2), ft_free_texture(cub), -1);
		cub->textures.west = ft_strtrim(&trim[i], " \n");
		if (cub->textures.west == NULL || ft_strcmp(cub->textures.west, "\0") == 0)
			return (ft_putendl_fd("WE is NULL or empty", 2), ft_free_texture(cub), -1);
	}
	return (0);
}

int	ft__second_mini_check(t_cub *cub, char *trim, int flag, int i)
{
	if (flag == 4)
	{
		if (cub->textures.east != NULL)
			return (ft_putendl_fd("EA already exits", 2), ft_free_texture(cub), -1);
		cub->textures.east = ft_strtrim(&trim[i], " \n");
		if (cub->textures.east == NULL || ft_strcmp(cub->textures.east, "\0") == 0)
			return (ft_putendl_fd("EA is NULL or empty", 2), ft_free_texture(cub), -1);	
	}
	else if (flag == 5)
	{
		if (cub->colors.floor != -1)
			return (ft_putendl_fd("F duplicated", 2), ft_free_texture(cub), -1);
		cub->colors.floor = ft_convert_hex(ft_strtrim(&trim[i], " \n"));
		if (cub->colors.floor == -1)
			return (ft_free_texture(cub), -1);
	}
	else if (flag == 6)
	{
		if (cub->colors.ceiling != -1)
			return (ft_putendl_fd("C duplicated", 2), ft_free_texture(cub), -1);
		cub->colors.ceiling = ft_convert_hex(ft_strtrim(&trim[i], " \n"));
		if (cub->colors.ceiling == -1)
			return (ft_free_texture(cub), -1);
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

int	ft_check_texture(char *str, t_cub	*cub)
{
	char	*tmp;
	char	*trim;
	int		i;

	i = 0;
	trim = ft_strtrim(str, " \n");
	tmp = ft_strtrim(str, " ");
	while (tmp && tmp[i] && tmp[i] != ' ')
		i++;
	tmp[i] = '\0';
	if (ft_check_something_else(trim) == 1)
		return (free(trim), free(tmp), -1);
	if (check_min_textute(cub, tmp, trim, i) != 0)
		return (-1);
	if (ft_check_colors(tmp, trim, cub, i) != 0)
		return (-1);
	return ((free(trim), free(tmp)), 0);
}

int	is_notonezero(char *line)
{
	int		i;
	char	*trim;

	i = 0;
	trim = ft_strtrim(line, " \n");
	if ((trim && trim[i] && trim[i] != '1'))
		return (ft_putstr_fd(trim , 2), ft_putendl_fd(" this is not valid to start map 1", 2), free(trim), 1);
	i++;
	free(trim);
	while (line[i])
	{
		if (line[i] && line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E' && line[i] != ' ' && line[i] != '\n')
			return (ft_putendl_fd("this is not valid to start map 2", 2), 1);
		i++;
	}
	return (0);
}

int	ft_config_map(int fd, t_cub *map)
{
	char    	*line;
	int			i;
	t_list_line	*list;

	map->config_count = 0;
	line = get_next_line(fd);
	if (!line)
		ft_putendl_fd("can't run cub3d on an empty map", 2), exit (1);
	list = NULL;
	while (line != NULL && map->config_count < 6)
	{

		if (ft_strcmp(line, "\n") == 0 || is_just_space(line))
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		if (ft_check_texture(line, map) != 0)
			return (free(line), -1);
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	map->map_started = 0;
	while (line != NULL)
	{
		if (is_just_space(line) == 0)
			map->map_started = 1;
		if (is_just_space(line) && map->map_started == 0)
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		if (is_notonezero(line))
			return (ft_free_texture(map), ft_clear_list(&list),free(line), 1);
		if (lst_addback(&list, line) == NULL)
			return (free(line), ft_free_texture(map), ft_clear_list(&list), 1);
		free(line);
		line = get_next_line(fd);
	}
	if (list == NULL)
		return (ft_putendl_fd("sorry but we think that you enter an invalid map like you are trying to run a file W/I 0 1", 2), ft_free_texture(map), ft_clear_list(&list), 1);
	map->list = list;
	int ret = parse_the_map(map, list);
	if (ret != 0)
		return (ret);
	return (0);
}
