/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_cub_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:49:53 by bbenaali          #+#    #+#             */
/*   Updated: 2025/09/14 16:38:29 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	count_map_ect(t_cub *game, int *i, int y)
{
	while (game->grind[y][(*i)])
	{
		if (check_pos_player(game->grind[y][(*i)], game))
		{
			game->player.pos_x = (*i) * TILE_SIZE + 32;
			game->player.pos_y = (game->colum - 1) * TILE_SIZE + 32;
		}
		(*i)++;
	}
}

void	count_map(t_cub *game)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	declared(game);
	while (game->grind[y][i])
		i++;
	game->row = --i;
	while (game->grind[y])
	{
		game->colum++;
		if (--i > game->row)
			game->row = i;
		i = 0;
		count_map_ect(game, &i, y);
		y++;
	}
}

int	is_wall(t_cub *data, double x, double y)
{
	int	tile_x;
	int	tile_y;

	if (x < 0 || y < 0)
		return (1);
	tile_x = floor(x / TILE_SIZE);
	tile_y = floor(y / TILE_SIZE);
	if (!data->grind || tile_x >= ft_strlen2(data->grind[tile_y]))
		return (0);
	if (data->grind[tile_y][tile_x] == '1')
		return (1);
	return (0);
}

void	my_pixel_put(t_cub *img, int x, int y, int color)
{
	int	offset;

	if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
		return ;
	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(img->addr + offset)) = color;
}

int	mouse_move(int x, int y, t_cub *data)
{
	int			delta_x;
	double		sensitivity;

	(void)y;
	if (data->last_x == -1)
		data->last_x = x;
	if (x < 0)
		x = 0;
	else if (x > WINDOW_WIDTH)
		x = WINDOW_WIDTH - 1;
	delta_x = x - data->last_x;
	sensitivity = 0.005;
	data->player.angle += delta_x * sensitivity;
	data->last_x = x;
	return (0);
}
