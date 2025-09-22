/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sexth_cub_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:57:29 by bbenaali          #+#    #+#             */
/*   Updated: 2025/09/14 16:07:50 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	ft_check_null(t_cub *data)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (i < 11)
	{
		if (data->anime[i].data == NULL)
			flag = 1;
		i++;
	}
	if (flag)
		return (ft_destroy_imag(data),
			write(2, "mlx_xpm_to_file faild\n", 22), 1);
	return (0);
}

void	*mlx_functions_xpm(t_cub *data, char *str, int i)
{
	return (mlx_xpm_file_to_image(data->mlx, str,
			&data->anime[i].width, &data->anime[i].height));
}

char	*mlx_function_data(t_cub *data, int i)
{
	return (mlx_get_data_addr(data->anime[i].data,
			&data->anime[i].bpp, &data->anime[i].line_len,
			&data->anime[i].endian));
}

int	get_data_for_animation_ect(t_cub *data)
{
	data->anime[0].addr = mlx_function_data(data, 0);
	data->anime[1].addr = mlx_function_data(data, 1);
	data->anime[2].addr = mlx_function_data(data, 2);
	data->anime[3].addr = mlx_function_data(data, 3);
	data->anime[4].addr = mlx_function_data(data, 4);
	data->anime[5].addr = mlx_function_data(data, 5);
	data->anime[6].addr = mlx_function_data(data, 6);
	data->anime[7].addr = mlx_function_data(data, 7);
	data->anime[8].addr = mlx_function_data(data, 8);
	data->anime[9].addr = mlx_function_data(data, 9);
	data->anime[10].addr = mlx_function_data(data, 10);
	if (ft_check_null_addr(data))
		return (ft_destroy_imag_textes(data), 1);
	return (0);
}

int	get_data_for_animation(t_cub *data)
{
	data->current_frame = 0;
	data->anime[0].data = mlx_functions_xpm(data, "image/01.xpm", 0);
	data->anime[1].data = mlx_functions_xpm(data, "image/02.xpm", 1);
	data->anime[2].data = mlx_functions_xpm(data, "image/03.xpm", 2);
	data->anime[3].data = mlx_functions_xpm(data, "image/04.xpm", 3);
	data->anime[4].data = mlx_functions_xpm(data, "image/05.xpm", 4);
	data->anime[5].data = mlx_functions_xpm(data, "image/06.xpm", 5);
	data->anime[6].data = mlx_functions_xpm(data, "image/07.xpm", 6);
	data->anime[7].data = mlx_functions_xpm(data, "image/08.xpm", 7);
	data->anime[8].data = mlx_functions_xpm(data, "image/09.xpm", 8);
	data->anime[9].data = mlx_functions_xpm(data, "image/10.xpm", 9);
	data->anime[10].data = mlx_functions_xpm(data, "image/11.xpm", 10);
	if (ft_check_null(data))
		return (ft_destroy_imag_textes(data), 1);
	if (get_data_for_animation_ect(data))
		return (1);
	return (0);
}
