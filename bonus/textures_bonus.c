/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:23:38 by bbenaali          #+#    #+#             */
/*   Updated: 2025/09/20 14:51:58 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static int	get_tex_index(t_cub *data)
{
	if (data->player.washitvertical)
	{
		if (data->player.face_left)
			return (3);
		return (0);
	}
	if (data->player.face_up)
		return (1);
	return (2);
}

static int	get_texture_x(t_cub *data, int tex_index)
{
	int	texture_x;

	if (data->player.washitvertical)
	{
		texture_x = (int)((fmod(data->player.final_distans_closer_y,
						TILE_SIZE) / TILE_SIZE)
				* data->textures.data[tex_index].width);
		if (data->player.face_left)
			texture_x = data->textures.data[tex_index].width - texture_x - 1;
	}
	else
	{
		texture_x = (int)((fmod(data->player.final_distans_closer_x,
						TILE_SIZE) / TILE_SIZE)
				* data->textures.data[tex_index].width);
		if (!data->player.face_up)
			texture_x = data->textures.data[tex_index].width - texture_x - 1;
	}
	return (texture_x);
}

static void	draw_wall(t_cub *data, int x, int wall_top,
		t_data_for_wall *var2)
{
	t_var_draw_wall	var;

	var.tex_index = get_tex_index(data);
	var.texture_x = get_texture_x(data, var.tex_index);
	var.step = (double)data->textures.data[var.tex_index].height
		/ var2->height_wall;
	var.tex_pos = 0;
	if (var2->height_wall > WINDOW_HEIGHT)
		var.tex_pos = ((var2->height_wall - WINDOW_HEIGHT) / 2) * var.step;
	var.y = wall_top;
	while (var.y < var2->wall_bottom && var.y < WINDOW_HEIGHT)
	{
		var.texture_y = (int)var.tex_pos;
		if (var.texture_y >= data->textures.data[var.tex_index].height)
			var.texture_y = data->textures.data[var.tex_index].height - 1;
		var.color = get_texture_pixel(&data->textures, var.texture_x,
				var.texture_y, var.tex_index);
		my_pixel_put(data, x, var.y, var.color);
		var.tex_pos += var.step;
		var.y++;
	}
}

static void	draw_ceiling_and_floor(t_cub *data, int x, int wall_top,
		t_data_for_wall *var)
{
	int	y;

	y = 0;
	while (y < wall_top)
	{
		my_pixel_put(data, x, y, data->colors.ceiling);
		y++;
	}
	draw_wall(data, x, wall_top, var);
	y = var->wall_bottom;
	while (y < WINDOW_HEIGHT)
	{
		my_pixel_put(data, x, y, data->colors.floor);
		y++;
	}
}

void	draw_vertical_wall_strip(t_cub *data, int x, int wall_top,
				int height_wall)
{
	t_data_for_wall	var;

	var.wall_bottom = wall_top + height_wall;
	if (wall_top < 0)
		wall_top = 0;
	var.height_wall = height_wall;
	draw_ceiling_and_floor(data, x, wall_top, &var);
}
