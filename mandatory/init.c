/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:42:27 by slimane           #+#    #+#             */
/*   Updated: 2025/09/17 09:19:32 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	lst_size(t_list_line *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

void	*lst_addback(t_list_line **list, char *line)
{
	t_list_line	*new;
	t_list_line	*tmp;

	new = malloc(sizeof(t_list_line) * 1);
	if (new == NULL)
		return (ft_putendl_fd("in malloc", 2), NULL);
	new->current = ft_strdup(line);
	if (!new->current)
		return (ft_putendl_fd("in strdup", 2), free(new), NULL);
	new->next = NULL;
	tmp = *list;
	if (!*list)
	{
		*list = new;
		return (*list);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (((void *)1));
}

int	ft_init_mlx(t_cub *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (-1);
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!mlx->win)
		return (free(mlx->mlx), -1);
	mlx->img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx->img)
		return (mlx_destroy_window(mlx->mlx, mlx->win), free(mlx->mlx), -1);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len,
			&mlx->endian);
	if (!mlx->addr)
		return (mlx_destroy_image(mlx->mlx, mlx->img),
			mlx_destroy_window(mlx->mlx, mlx->win), free(mlx->mlx), -1);
	return (0);
}

void	init_texture(t_cub *cub)
{
	if ((WINDOW_WIDTH < 0 || WINDOW_WIDTH > 8192)
		|| (WINDOW_HEIGHT < 0 || WINDOW_HEIGHT > 8192))
		(ft_putendl_fd("you have reached the max or min of window", 2),
			exit(1));
	cub->textures.north = NULL;
	cub->textures.south = NULL;
	cub->textures.west = NULL;
	cub->textures.east = NULL;
	cub->colors.floor = -1;
	cub->colors.ceiling = -1;
	cub->last_x = -1;
}
