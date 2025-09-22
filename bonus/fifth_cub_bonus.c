/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifth_cub_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:54:21 by bbenaali          #+#    #+#             */
/*   Updated: 2025/09/14 16:27:28 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static	int	load_texture(void *mlx, t_data_text *texture, char *path)
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

void	rendring_wall_s(t_cub *data)
{
	t_variables	var;

	var.start_angle = data->player.angle - (FOV_ANGLE / 2);
	var.i = 0;
	var.distanceprojectionplane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	var.old_angle = data->player.angle;
	while (var.i < NUM_RAYS)
	{
		data->player.angle = var.start_angle + var.i * (FOV_ANGLE / NUM_RAYS);
		fice_vision(data);
		var.ray_distance = for_cast(data);
		var.corrected_distance = var.ray_distance * cos(data->player.angle
				- var.old_angle);
		var.wall_strip_height = (int)((TILE_SIZE / var.corrected_distance)
				* var.distanceprojectionplane);
		var.wall_top_pixel = (WINDOW_HEIGHT / 2) - (var.wall_strip_height / 2);
		draw_vertical_wall_strip(data, var.i,
			var.wall_top_pixel, var.wall_strip_height);
		var.i++;
	}
	data->player.angle = var.old_angle;
}

void	rendring_animation(t_cub *data)
{
	t_rendring_animation	var;

	var.y = 0;
	var.x = 0;
	var.frame = data->current_frame % NUM_FRAMES;
	var.start_x = (WINDOW_WIDTH / 2) - (data->anime[var.frame].width / 2);
	var.start_y = WINDOW_HEIGHT - data->anime[var.frame].height;
	while (var.y < data->anime[var.frame].height)
	{
		var.x = 0;
		while (var.x < data->anime[var.frame].width)
		{
			var.color = get_texture_pixel_02(data->anime, var.x, var.y,
					var.frame);
			if ((var.color & 0x00FFFFFF) != 0x000000)
				my_pixel_put(data, var.start_x + var.x, var.start_y + var.y,
					var.color);
			var.x++;
		}
		var.y++;
	}
}

int	ft_draw(t_cub *data)
{
	update_player(data);
	mlx_clear_window(data->mlx, data->win);
	rendring_wall_s(data);
	rendring_animation(data);
	data->current_frame++;
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
