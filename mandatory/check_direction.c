/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:29:16 by slimane           #+#    #+#             */
/*   Updated: 2025/09/14 12:00:28 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_north(t_list_line *prev, int i)
{
	if (!prev || (int)ft_strlen(prev->current) < i
		|| (prev->current[i] != '1' && prev->current[i] != '0'
			&& prev->current[i] != 'N' && prev->current[i] != 'S'
			&& prev->current[i] != 'E' && prev->current[i] != 'W'))
		return (ft_putendl_fd("invalid unclose map in north", 2), 1);
	return (0);
}

int	check_south(t_list_line *next, int i)
{
	if (!next || (int)ft_strlen(next->current) < i
		|| (next->current[i] != '1' && next->current[i] != '0'
			&& next->current[i] != 'N' && next->current[i] != 'S'
			&& next->current[i] != 'E' && next->current[i] != 'W'))
		return (ft_putendl_fd("invalid unclose map in south", 2), 1);
	return (0);
}

int	check_east(t_list_line *curr, int i)
{
	if (curr->current[i - 1] != '1' && curr->current[i - 1] != '0'
		&& curr->current[i - 1] != 'N' && curr->current[i - 1] != 'S'
		&& curr->current[i - 1] != 'E' && curr->current[i - 1] != 'W')
		return (ft_putendl_fd("invalid unclose map in left", 2), 1);
	return (0);
}

int	check_west(t_list_line *curr, int i)
{
	if (curr->current[i + 1] != '1' && curr->current[i + 1] != '0'
		&& curr->current[i + 1] != 'N' && curr->current[i + 1] != 'S'
		&& curr->current[i + 1] != 'E' && curr->current[i + 1] != 'W')
		return (ft_putendl_fd("invalid unclose map in right", 2), 1);
	return (0);
}
