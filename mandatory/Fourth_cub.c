/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fourth_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:30:10 by bbenaali          #+#    #+#             */
/*   Updated: 2025/09/17 07:44:35 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	fice_vision(t_cub *data)
{
	normalize_angle(&data->player.angle);
	if (data->player.angle > 0 && data->player.angle < M_PI)
		data->player.face_down = 1;
	else
		data->player.face_down = 0;
	data->player.face_up = !data->player.face_down;
	if (data->player.angle < M_PI / 2 || data->player.angle > 3 * M_PI / 2)
		data->player.face_right = 1;
	else
		data->player.face_right = 0;
	data->player.face_left = !data->player.face_right;
}

double	ft_calcul_vitaghors(t_cub *data, double x, double y)
{
	return (sqrt((x - data->player.pos_x) * (x - data->player.pos_x)
			+ (y - data->player.pos_y) * (y - data->player.pos_y)));
}

int	get_texture_pixel(t_textures *data, int x, int y, int i)
{
	int	offset;

	if (x < 0 || y < 0 || x >= data->data[i].width || y >= data->data[i].height)
		return (-1);
	offset = (data->data[i].line_len * y) + (x * (data->data[i].bpp / 8));
	return (*((unsigned int *)(data->data[i].addr + offset)));
}

int	get_texture_pixel_02(t_animation *data, int x, int y, int i)
{
	int	offset;

	if (x < 0 || y < 0 || x >= data[i].width || y >= data[i].height)
		return (-1);
	offset = (data[i].line_len * y) + (x * (data[i].bpp / 8));
	return (*((unsigned int *)(data[i].addr + offset)));
}

void	rendring_wall_s(t_cub *data)
{
	t_variables	var;

	var.i = 0;
	var.start_angle = data->player.angle - (FOV_ANGLE / 2);
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
