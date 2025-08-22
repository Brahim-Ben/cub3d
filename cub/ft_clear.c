/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:08:06 by slimane           #+#    #+#             */
/*   Updated: 2025/07/20 18:57:25 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_clear_list(t_list_line **list)
{
	t_list_line	*tmp;

	while (*list != NULL)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->current);
		free(tmp);
	}
	free(*list);
}

void	ft_free_texture(t_cub *cub)
{
	if (cub->textures.north)
		free(cub->textures.north);
	if (cub->textures.south)
		free(cub->textures.south);
	if (cub->textures.west)
		free(cub->textures.west);
	if (cub->textures.east)
		free(cub->textures.east);
}
