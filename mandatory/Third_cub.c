/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Third_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:53:47 by slimane           #+#    #+#             */
/*   Updated: 2025/09/20 14:53:48 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	key_press(int keycode, void *player2)
{
	t_cub	*player;

	player = (t_cub *)player2;
	if (keycode == 13)
		player->player.var.w = 1;
	if (keycode == 1)
		player->player.var.s = 1;
	if (keycode == 0)
		player->player.var.a = 1;
	if (keycode == 2)
		player->player.var.d = 1;
	if (keycode == 123)
		player->player.var.left = 1;
	if (keycode == 124)
		player->player.var.right = 1;
	if (keycode == 53)
	{
		ft_destroy_imag_textes(player);
		ft_destroy_mlx(player);
		(fr_text(player), close(player->fd));
		(ft_free(player->grind, -1), ft_clear_list(&player->list));
		exit(0);
	}
	return (0);
}

int	key_release(int keycode, void *player2)
{
	t_cub	*player;

	player = (t_cub *)player2;
	if (keycode == 13)
		player->player.var.w = 0;
	if (keycode == 1)
		player->player.var.s = 0;
	if (keycode == 0)
		player->player.var.a = 0;
	if (keycode == 2)
		player->player.var.d = 0;
	if (keycode == 123)
		player->player.var.left = 0;
	if (keycode == 124)
		player->player.var.right = 0;
	return (0);
}

static int	can_move(t_cub *data, double x, double y, int margin)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (data->grind[map_y][map_x] == '1')
		return (0);
	if (data->grind[(int)((y - margin) / TILE_SIZE)][map_x] == '1'
		|| data->grind[(int)((y + margin) / TILE_SIZE)][map_x] == '1')
		return (0);
	if (data->grind[map_y][(int)((x - margin) / TILE_SIZE)] == '1'
		|| data->grind[map_y][(int)((x + margin) / TILE_SIZE)] == '1')
		return (0);
	if (data->grind[(int)((y - margin) / TILE_SIZE)]
		[(int)(x - margin) / TILE_SIZE] == '1'
		|| data->grind[(int)((y + margin) / TILE_SIZE)]
		[(int)(x + margin) / TILE_SIZE] == '1')
		return (0);
	if (data->grind[(int)((y + margin) / TILE_SIZE)]
		[(int)(x - margin) / TILE_SIZE] == '1')
		return (0);
	if (data->grind[(int)((y - margin) / TILE_SIZE)]
		[(int)(x + margin) / TILE_SIZE] == '1')
		return (0);
	return (1);
}

static void	update_player_ect(t_cub *player, t_update_player *var)
{
	if (player->player.var.w)
	{
		var->new_x += cos(player->player.angle) * var->move_step;
		var->new_y += sin(player->player.angle) * var->move_step;
	}
	if (player->player.var.s)
	{
		var->new_x -= cos(player->player.angle) * var->move_step;
		var->new_y -= sin(player->player.angle) * var->move_step;
	}
	if (player->player.var.a)
	{
		var->new_x += cos(player->player.angle - M_PI / 2) * var->move_step;
		var->new_y += sin(player->player.angle - M_PI / 2) * var->move_step;
	}
	if (player->player.var.d)
	{
		var->new_x += cos(player->player.angle + M_PI / 2) * var->move_step;
		var->new_y += sin(player->player.angle + M_PI / 2) * var->move_step;
	}
}

void	update_player(t_cub *player)
{
	t_update_player	var;

	var.new_x = player->player.pos_x;
	var.new_y = player->player.pos_y;
	var.move_step = 6;
	var.margin = 16;
	update_player_ect(player, &var);
	if (player->player.var.left)
		player->player.angle -= 3 * (M_PI / 180);
	if (player->player.var.right)
		player->player.angle += 3 * (M_PI / 180);
	if (can_move(player, var.new_x, player->player.pos_y, var.margin))
		player->player.pos_x = var.new_x;
	if (can_move(player, player->player.pos_x, var.new_y, var.margin))
		player->player.pos_y = var.new_y;
}
