/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray-casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:58:25 by bbenaali          #+#    #+#             */
/*   Updated: 2025/09/14 11:35:19 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static double	ft_loop_horzontl(t_cub *data, double *hit_x, double *hit_y)
{
	double	x;
	double	y;
	double	tmp_y;

	x = data->player.inter_x;
	y = data->player.inter_y;
	while (x >= 0 && x <= data->size_x && y >= 0 && y <= data->size_y)
	{
		tmp_y = y;
		if (data->player.face_up)
			tmp_y = y - 1;
		if (is_wall(data, x, tmp_y))
			return (*hit_x = x, *hit_y = y, ft_calcul_vitaghors(data, x, y));
		x += data->player.step_x;
		y += data->player.step_y;
	}
	return (INT_MAX);
}

static double	check_horizontal(t_cub *data, double *hit_x, double *hit_y)
{
	data->player.inter_y = floor(data->player.pos_y / TILE_SIZE) * TILE_SIZE;
	if (data->player.face_down)
		data->player.inter_y += TILE_SIZE;
	data->player.inter_x = data->player.pos_x
		+ (data->player.inter_y - data->player.pos_y) / tan(data->player.angle);
	data->player.step_y = TILE_SIZE;
	if (data->player.face_up)
		data->player.step_y *= -1;
	data->player.step_x = TILE_SIZE / tan(data->player.angle);
	if ((data->player.face_left && data->player.step_x > 0)
		|| (data->player.face_right && data->player.step_x < 0))
		data->player.step_x *= -1;
	return (ft_loop_horzontl(data, hit_x, hit_y));
}

static double	ft_loop_vertical(t_cub *data, double *hit_x, double *hit_y)
{
	double	x;
	double	y;
	double	tmp_x;

	x = data->player.inter_x;
	y = data->player.inter_y;
	while (x >= 0 && x <= data->size_x && y >= 0 && y <= data->size_y)
	{
		tmp_x = x;
		if (data->player.face_left)
			tmp_x = x - 1;
		if (is_wall(data, tmp_x, y))
			return (*hit_x = x, *hit_y = y, ft_calcul_vitaghors(data, x, y));
		x += data->player.step_x;
		y += data->player.step_y;
	}
	return (INT_MAX);
}

static double	check_vertical(t_cub *data, double *hit_x, double *hit_y)
{
	data->player.inter_x = floor(data->player.pos_x / TILE_SIZE) * TILE_SIZE;
	if (data->player.face_right)
		data->player.inter_x += TILE_SIZE;
	data->player.inter_y = data->player.pos_y
		+ (data->player.inter_x - data->player.pos_x) * tan(data->player.angle);
	data->player.step_x = TILE_SIZE;
	if (data->player.face_left)
		data->player.step_x *= -1;
	data->player.step_y = TILE_SIZE * tan(data->player.angle);
	if ((data->player.face_up && data->player.step_y > 0)
		|| (data->player.face_down && data->player.step_y < 0))
		data->player.step_y *= -1;
	return (ft_loop_vertical(data, hit_x, hit_y));
}

double	for_cast(t_cub *data)
{
	t_var_for_cast	var;

	var.hit_x = 0;
	var.hit_y = 0;
	var.vhit_x = 0;
	var.vhit_y = 0;
	var.hdist = check_horizontal(data, &var.hit_x, &var.hit_y);
	var.vdist = check_vertical(data, &var.vhit_x, &var.vhit_y);
	if (var.vdist < var.hdist)
	{
		data->player.final_distans_closer_x = var.vhit_x;
		data->player.final_distans_closer_y = var.vhit_y;
		data->player.washitvertical = true;
		return (var.vdist);
	}
	data->player.final_distans_closer_x = var.hit_x;
	data->player.final_distans_closer_y = var.hit_y;
	data->player.washitvertical = false;
	return (var.hdist);
}
