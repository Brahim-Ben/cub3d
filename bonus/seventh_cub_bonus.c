/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seventh_cub_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:00:41 by bbenaali          #+#    #+#             */
/*   Updated: 2025/09/14 16:05:04 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static char	**ft_convert_list_ect(t_list_line *list, char **map)
{
	int			i;
	int			j;
	t_list_line	*tmp;

	tmp = list;
	i = 0;
	j = 0;
	while (list)
	{
		map[j] = ft_strdup(list->current);
		if (!map[j])
		{
			while (i < j)
				free(map[i++]);
			free(map);
			return (list = tmp, NULL);
		}
		j++;
		list = list->next;
	}
	map[j] = NULL;
	return (list = tmp, map);
}

char	**ft_convert_list(t_list_line *list)
{
	char		**map;
	int			len;
	t_list_line	*tmp;

	len = 0;
	tmp = list;
	if (!list)
		return (NULL);
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	map = malloc(sizeof(char *) * (len + 1));
	if (!map)
		return (NULL);
	return (ft_convert_list_ect(list, map));
}

void	ft_destroy_imag_textes(t_cub *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(data->mlx, data->textures.data[i].data);
		i++;
	}
}

void	ft_destroy_imag(t_cub *data)
{
	int	i;

	i = 0;
	while (i < 11)
	{
		if (data->anime[i].data)
			mlx_destroy_image(data->mlx, data->anime[i].data);
		i++;
	}
}

int	ft_check_null_addr(t_cub *data)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (i < 11)
	{
		if (data->anime[i].addr == NULL)
			flag = 1;
		i++;
	}
	if (flag)
		return (ft_destroy_imag(data),
			write(2, "mlx_get_data_addr faild\n", 22), 1);
	return (0);
}
