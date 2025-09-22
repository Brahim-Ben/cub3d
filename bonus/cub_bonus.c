/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:00:48 by slimane           #+#    #+#             */
/*   Updated: 2025/09/20 19:47:08 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	ft_mlx_functions(t_cub *game)
{
	count_map(game);
	if (ft_init_cub(game) == -1)
		(ft_clear_list(&game->list), fr_text(game),
			ft_free(game->grind, -1), ft_putendl_fd("In mlx", 2),
			close(game->fd), exit(1));
	if (get_data_for_images(game) || get_data_for_animation(game))
		(ft_clear_list(&game->list), fr_text(game),
			ft_free(game->grind, -1), ft_destroy_mlx(game),
			close(game->fd), exit(1));
	mlx_hook(game->win, 2, 0, key_press, game);
	mlx_hook(game->win, 3, 0, key_release, game);
	mlx_hook(game->win, 6, 0, mouse_move, game);
	mlx_hook(game->win, 17, 0, ft_close, game);
	mlx_loop_hook(game->mlx, ft_draw, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_cub	game;
	int		sort;

	if (ac != 2)
		return (ft_putendl_fd("Usage: ./cub3D <path/to/map.cub>", 2), 1);
	init_texture(&game);
	game.fd = ft_open_map(av[1]);
	if (game.fd == -1)
		return (ft_putendl_fd("open faild", 2), 1);
	sort = ft_config_map(game.fd, &game);
	if (sort != 0)
		return (close(game.fd), sort);
	game.grind = ft_convert_list(game.list);
	if (!game.grind)
		return (ft_clear_list(&game.list), fr_text(&game),
			ft_free(game.grind, -1),
			ft_putendl_fd("Failed to convert list to map or \
allocation", 2), close(game.fd), 1);
	ft_mlx_functions(&game);
	return (0);
}
