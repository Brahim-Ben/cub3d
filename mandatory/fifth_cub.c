/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifth_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:35:25 by bbenaali          #+#    #+#             */
/*   Updated: 2025/09/14 14:39:57 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	**ft_convert_list_ect(t_list_line *list, char **map)
{
	int			i;
	int			j;
	t_list_line	*tmp;

	tmp = list;
	i = 0;
	j = 0;
	while (list)
	{
		map[j] = ft_strdup(list->current);
		if (!map[j])
		{
			while (i < j)
				free(map[i++]);
			free(map);
			return (list = tmp, NULL);
		}
		j++;
		list = list->next;
	}
	map[j] = NULL;
	return (list = tmp, map);
}

char	**ft_convert_list(t_list_line *list)
{
	char		**map;
	int			len;
	t_list_line	*tmp;

	len = 0;
	tmp = list;
	if (!list)
		return (NULL);
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	map = malloc(sizeof(char *) * (len + 1));
	if (!map)
		return (NULL);
	return (ft_convert_list_ect(list, map));
}

static int	load_texture(void *mlx, t_data_text *texture, char *path)
{
	texture->data = mlx_xpm_file_to_image(mlx, path,
			&texture->width, &texture->height);
	if (!texture->data)
		return (write(2, "Error loading textures\n", 24), 1);
	texture->addr = mlx_get_data_addr(texture->data, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!texture->addr)
		return (write(2, "Error loading textures\n", 24), 1);
	return (0);
}

int	get_data_for_images(t_cub *data)
{
	if (load_texture(data->mlx, &data->textures.data[0], data->textures.east))
		return (1);
	if (load_texture(data->mlx, &data->textures.data[1], data->textures.north))
		return (mlx_destroy_image(data->mlx, data->textures.data[0].data), 1);
	if (load_texture(data->mlx, &data->textures.data[2], data->textures.south))
		return (mlx_destroy_image(data->mlx, data->textures.data[1].data),
			mlx_destroy_image(data->mlx, data->textures.data[0].data), 1);
	if (load_texture(data->mlx, &data->textures.data[3], data->textures.west))
		return (mlx_destroy_image(data->mlx, data->textures.data[2].data),
			mlx_destroy_image(data->mlx, data->textures.data[1].data),
			mlx_destroy_image(data->mlx, data->textures.data[0].data), 1);
	return (0);
}

int	ft_draw(t_cub *data)
{
	update_player(data);
	mlx_clear_window(data->mlx, data->win);
	rendring_wall_s(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
