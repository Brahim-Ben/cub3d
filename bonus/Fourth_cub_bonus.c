/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fourth_cub_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:46:09 by bbenaali          #+#    #+#             */
/*   Updated: 2025/09/14 16:07:37 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	normalize_angle(double *angle)
{
	*angle = fmod(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle += 2 * M_PI;
}

void	fice_vision(t_cub *data)
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
