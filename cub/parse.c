/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:24:45 by slimane           #+#    #+#             */
/*   Updated: 2025/07/20 18:34:25 by slimane          ###   ########.fr       */
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
	return (0);
}

int	ft_parse_line(t_list_line *prev, t_list_line *curr, t_list_line	*next, t_cub *cub)
{
	int	i;

	i = 0;
	if (!curr)
		return  (5); 
	while (curr->current[i])
	{
		if (curr->current[i] == '0' || curr->current[i] == 'N' || curr->current[i] == 'S' || curr->current[i] == 'W' || curr->current[i] == 'E')
		{
			
			if (!prev || (int)ft_strlen(prev->current) < i || (prev->current[i] != '1' && prev->current[i] != '0' && prev->current[i] != 'N' && prev->current[i] != 'S' && prev->current[i] != 'E' && prev->current[i] != 'W')) // fo9
				return (ft_free_texture(cub), ft_putendl_fd("ERROR invalid unclose map in north", 2), ft_clear_list(&cub->list), 10);
			if (!next || (int)ft_strlen(next->current) < i || (next->current[i] != '1' && next->current[i] != '0' && next->current[i] != 'N' && next->current[i] != 'S' && next->current[i] != 'E' && next->current[i] != 'W')) // te7t
				return (ft_free_texture(cub), ft_putendl_fd("ERROR invalid unclose map in south", 2), ft_clear_list(&cub->list), 15);
			if (curr->current[i - 1] != '1' && curr->current[i - 1] != '0'  && curr->current[i - 1] != 'N' && curr->current[i - 1] != 'S' && curr->current[i - 1] != 'E' && curr->current[i - 1] != 'W') // lisser
				return (ft_free_texture(cub), ft_putendl_fd("ERROR invalid unclose map in left", 2), ft_clear_list(&cub->list), 20);
			if (curr->current[i + 1] != '1' && curr->current[i + 1] != '0'  && curr->current[i + 1] != 'N' && curr->current[i + 1] != 'S' && curr->current[i + 1] != 'E' && curr->current[i + 1] != 'W') // limen 
				return (ft_free_texture(cub), ft_putendl_fd("ERROR invalid unclose map in right", 2), ft_clear_list(&cub->list), 25);
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
	i = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->current[i] != '\0')
		{
			if (tmp->current[i] && (tmp->current[i] == 'N' || tmp->current[i] == 'S' || tmp->current[i] == 'E' || tmp->current[i] == 'W'))
				count++;
			if (count > 1)
				return (puts("ERROR MORE THAN one player"), -1);
			i++;
		}
		tmp = tmp->next;
	}
	if (count == 0)
		return (puts("ERROR NO player in MAP"), -1);
	return (1);
}

int	parse_the_map(t_cub *cub, t_list_line *list)
{
	t_list_line	*tmp;
	t_list_line	*prev;
	t_list_line	*next;
	int			i;
	int			line_marked;
	int			status;

	tmp = list;
	i = 0;
	while (tmp && ft_is_empty(tmp->current))
		tmp = tmp->next;
	prev = NULL;
	next = tmp->next;
	cub->map_started = 1;
	line_marked = 0;
	while (tmp)
	{
		if (ft_strrchr(tmp->current, '0') || ft_strrchr(tmp->current, 'N') || ft_strrchr(tmp->current, 'S') || ft_strrchr(tmp->current, 'W') || ft_strrchr(tmp->current, 'E'))
		{
			status = ft_parse_line(prev, tmp, next, cub);
			if (status != 0)
				return (status);
		}
		prev = tmp;
		tmp = tmp->next;
		if (tmp)
			next = tmp->next;
		else
			next = NULL;
	}
	if (ft_parse_player(list) == -1)
		return (ft_clear_list(&list), ft_free_texture(cub), 30);
	return (0);
}