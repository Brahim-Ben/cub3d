/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:24:41 by slimane           #+#    #+#             */
/*   Updated: 2025/07/10 15:46:48 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    ft_destroy_mlx(t_cub *cub)
{
    mlx_destroy_image(cub->mlx, cub->img);
    mlx_destroy_window(cub->mlx, cub->win);
}