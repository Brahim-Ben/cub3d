/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:32:12 by slimane           #+#    #+#             */
/*   Updated: 2025/09/20 14:40:31 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_check_texture(char *str, t_cub	*cub)
{
	char	*tmp;
	char	*trim;
	int		i;

	i = 0;
	trim = ft_strtrim(str, " \n");
	tmp = ft_strtrim(str, " \n");
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
		return (ft_putstr_fd(
				"ERROR this is not valid to start map ", 2),
			ft_putstr_fd(trim, 2), ft_putstr_fd("\n", 2), free(trim), 1);
	i++;
	free(trim);
	trim = NULL;
	while (line[i])
	{
		if (line[i] && line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != 'E'
			&& line[i] != ' ' && line[i] != '\n')
			return (ft_putstr_fd("ERROR this is not valid to in map: ", 2),
				write(2, &line[i], 1), write(2, "\n", 1), 1);
		i++;
	}
	return (0);
}

char	*ft_put_texture(t_cub *map, int fd)
{
	char	*line;

	map->config_count = 0;
	line = get_next_line(fd);
	if (!line)
		return (ft_putendl_fd("can't run cub3d on an empty map", 2), NULL);
	while (line != NULL && map->config_count < 6)
	{
		if (ft_strcmp(line, "\n") == 0 || is_just_space(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (ft_check_texture(line, map) != 0)
			return (free(line), line = NULL, NULL);
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

int	generate_list(int fd, t_cub *map, t_list_line **list, char *line)
{
	while (line != NULL)
	{
		if (is_just_space(line) == 0)
			map->map_started = 1;
		if (is_just_space(line) && map->map_started == 0)
		{
			(free(line), line = get_next_line(fd));
			continue ;
		}
		if (is_notonezero(line))
			return (fr_text(map), ft_clear_list(list), free(line), 1);
		if (lst_addback(list, line) == NULL)
			return (free(line), fr_text(map), ft_clear_list(list), 1);
		(free(line), line = get_next_line(fd));
	}
	return (0);
}

int	ft_config_map(int fd, t_cub *map)
{
	char		*line;
	t_list_line	*list;
	int			ret;

	list = NULL;
	map->map_started = 0;
	line = ft_put_texture(map, fd);
	if (!line)
		return (fr_text(map), -1);
	if (generate_list(fd, map, &list, line))
		return (-1);
	if (list == NULL)
		return (ft_putendl_fd(
				"sorry but we think that you enter an invalid map\
like you are trying to run a file W/I 0 1", 2),
			fr_text(map), 1);
	map->list = list;
	ret = parse_the_map(map, list);
	if (ret != 0)
		return (ret);
	return (0);
}
