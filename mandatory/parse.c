/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:24:45 by slimane           #+#    #+#             */
/*   Updated: 2025/09/20 20:16:59 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_is_empty(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_parse_line(t_list_line *prev, t_list_line *curr, t_list_line	*next,
	t_cub *cub)
{
	int	i;

	i = 0;
	if (!curr)
		return (5);
	while (curr->current[i])
	{
		if (curr->current[i] == '0' || curr->current[i] == 'N'
			|| curr->current[i] == 'S' || curr->current[i] == 'W'
			|| curr->current[i] == 'E')
		{
			if (check_north(prev, i) == 1)
				return (fr_text(cub), ft_clear_list(&cub->list), 10);
			if (check_south(next, i))
				return (fr_text(cub), ft_clear_list(&cub->list), 15);
			if (check_east(curr, i))
				return (fr_text(cub), ft_clear_list(&cub->list), 20);
			if (check_west(curr, i))
				return (fr_text(cub), ft_clear_list(&cub->list), 25);
		}
		i++;
	}
	return (0);
}

int	ft_parse_player(t_list_line *list)
{
	t_list_line	*tmp;
	int			count;
	int			i;

	tmp = list;
	if (!tmp)
		return (-1);
	count = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->current[i] != '\0')
		{
			if ((tmp->current[i] == 'N' || tmp->current[i] == 'S'
					|| tmp->current[i] == 'E' || tmp->current[i] == 'W'))
				count++;
			if (count > 1)
				return (ft_putendl_fd("MORE THAN one player", 2), -1);
			i++;
		}
		tmp = tmp->next;
	}
	if (count == 0)
		return (ft_putendl_fd("NO player in MAP", 2), -1);
	return (1);
}

int	check_char(t_list_line *tmp, t_list_line *prev, t_list_line *next,
				t_cub *cub)
{
	int	status;

	status = 0;
	if (ft_strrchr(tmp->current, '0') || ft_strrchr(tmp->current, 'N')
		|| ft_strrchr(tmp->current, 'S') || ft_strrchr(tmp->current, 'W')
		|| ft_strrchr(tmp->current, 'E'))
	{
		status = ft_parse_line(prev, tmp, next, cub);
		if (status != 0)
			return (status);
	}
	return (0);
}

int	parse_the_map(t_cub *cub, t_list_line *list)
{
	t_list_line	*tmp;
	t_list_line	*prev;
	t_list_line	*next;

	tmp = list;
	while (tmp && ft_is_empty(tmp->current))
		tmp = tmp->next;
	cub->map_started = 1;
	prev = NULL;
	while (tmp)
	{
		if (check_char(tmp, prev, next, cub) != 0)
			return (-1);
		prev = tmp;
		tmp = tmp->next;
		if (tmp)
			next = tmp->next;
		else
			next = NULL;
	}
	if (ft_parse_player(list) == -1)
		return (ft_clear_list(&list), fr_text(cub), 30);
	return (0);
}
