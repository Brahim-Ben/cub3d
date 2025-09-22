/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:18:09 by bbenaali          #+#    #+#             */
/*   Updated: 2025/09/17 16:22:21 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_init_cub(t_cub *cub)
{
	cub->size_y = cub->colum * TILE_SIZE;
	cub->size_x = cub->row * TILE_SIZE;
	cub->player.var.a = 0;
	cub->player.var.w = 0;
	cub->player.var.s = 0;
	cub->player.var.d = 0;
	cub->player.var.left = 0;
	cub->player.var.right = 0;
	cub->player.face_down = 0;
	cub->player.face_up = 0;
	cub->player.face_left = 0;
	cub->player.face_right = 0;
	if (ft_init_mlx(cub) == -1)
		return (-1);
	return (0);
}

int	ft_open_map(char *str)
{
	char	*ext;
	int		fd;

	ext = ft_strrchr(str, '.');
	if (ext == NULL || ft_strcmp(ext, ".cub") != 0)
		return (ft_putendl_fd("invalid map extention", 2), -1);
	fd = open(str, O_RDONLY, 0777);
	if (fd == -1)
		return (perror("cub3d:"), -1);
	return (fd);
}

int	ft_close(t_cub *mlx)
{
	ft_destroy_imag_textes(mlx);
	ft_destroy_mlx(mlx);
	fr_text(mlx);
	ft_clear_list(&mlx->list);
	close(mlx->fd);
	exit(0);
	return (0);
}

int	check_pos_player(char c, t_cub *data)
{
	if (c == 'S')
		return (data->player.angle = M_PI / 2, 1);
	if (c == 'N')
		return (data->player.angle = 3 * M_PI / 2, 1);
	if (c == 'E')
		return (data->player.angle = 0, 1);
	if (c == 'W')
		return (data->player.angle = M_PI, 1);
	return (0);
}

void	declared(t_cub *game)
{
	game->row = 0;
	game->colum = 0;
	game->player.pos_x = 0;
	game->player.pos_y = 0;
}
