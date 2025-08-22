/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:42:43 by slimane           #+#    #+#             */
/*   Updated: 2025/07/19 17:15:51 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    ft_build_2d_map(t_cub *cub)
{
	t_list_line	*list;
	int			pos_y;
	int			i;

	list = cub->list;
	i = 0;
	pos_y = 0;
	while (list)
	{
		i = 0;
		while (list->current && list->current[i])
		{
			 
			i++;
		}
		pos_y++;
		list = list->next;
	}
		
}