/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:00:48 by slimane           #+#    #+#             */
/*   Updated: 2025/08/22 11:12:59 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_init_cub(t_cub *cub)
{
	cub->size_y = cub->colum * TILE_SIZE;
	cub->size_x = cub->row * TILE_SIZE;
	cub->player.var.a = 0;
	cub->player.var.w = 0;
	cub->player.var.s = 0;
	cub->player.var.d = 0;
	cub->player.var.left = 0;
	cub->player.var.right = 0;
	cub->player.face_down = 0;
	cub->player.face_up = 0;
	cub->player.face_left = 0;
	cub->player.face_right = 0;
	if (ft_init_mlx(cub) == -1)
		return (-1);
	return (0);
}

int	ft_open_map(char *str)
{
	char	*ext;
	int		fd;

	ext = ft_strrchr(str, '.');
	if (ext == NULL || ft_strcmp(ext, ".cub") != 0)
		return (ft_putendl_fd("invalid map extention", 2), -1);
	fd = open(str, O_RDONLY, 0777);
	if (fd == -1)
		return (perror("cub3d:"), -1);
	return (fd);
}

int	ft_close(t_cub *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->textures.north);
	free(mlx->textures.south);
	free(mlx->textures.east);
	free(mlx->textures.west);
	ft_clear_list(&mlx->list);
	exit(0);
	return (0);
}


int	check_pos_player(char c, t_cub *data)
{
	if(c == 'S')
		return (data->player.angle = M_PI / 2, 1);
	if(c == 'N')
		return (data->player.angle = 3 * M_PI / 2, 1);
	if (c == 'E')
		return (data->player.angle = 0, 1);
	if (c == 'W')
		return (data->player.angle = M_PI, 1);
	return (0);
}

void count_map(t_cub *game)
{
	int i;

	i = 0;
	game->row = 0;
	game->colum = 0;
	game->player.pos_x = 0;
	game->player.pos_y = 0;
	t_list_line *tmp = game->list;
	while(game->list->current[i])
		i++;
	game->row = --i;
	while(game->list)
	{
		// printf("%lu\n", strlen(game->list->current));
		// printf("%s\n", game->list->current);
		game->colum++;
		if(--i > game->row)
			game->row = i;
		i = 0;
		while(game->list->current[i])
		{
			if(check_pos_player(game->list->current[i], game))
				game->player.pos_x = i * TILE_SIZE + 32, game->player.pos_y = (game->colum - 1) * TILE_SIZE + 32;
			i++;
		}
		game->list = game->list->next;
	}
	game->list = tmp;
	// printf("%f\n", game->player.pos_x);
	// exit(1);
}


int is_wall(t_cub *data, double x, double y)
{
	int tile_x;
	int tile_y;
	// t_list_line *tmp = data->list;
	// int i = 0;

	if (x < 0 || y < 0)
		return (1);

	// if (fmod(x, TILE_SIZE) == 0)
	// 	x += (data->player.face_left ? -0.0001 : 0.0001);
	// if (fmod(y, TILE_SIZE) == 0)
	// 	y += (data->player.face_up ? -0.0001 : 0.0001);

	tile_x = floor(x / TILE_SIZE);
	tile_y = floor(y / TILE_SIZE);
	// while (i < tile_y && data->list)
	// {
	//     data->list = data->list->next;
	//     i++;
	// }
	if (!data->grind || tile_x >= ft_strlen2(data->grind[tile_y]))
		return (1);

	if (data->grind[tile_y][tile_x] == '1')
		return (1);
		
	return (0);
}


// int is_wall(t_cub *data, int x, int y)
// {
//     int tile_x = floor(x / TILE_SIZE);
// 	int i = 0;

// 	t_list_line *tmp = data->list;
// 	// if(data->player.face_up)
// 	// 	if(y > 0)
// 	// 		y--;
// 	while(i <  y / TILE_SIZE && data->list)
// 	{
// 		data->list = data->list->next;
// 		i++;
// 	}
// 	if(!data->list || !data->list->current[tile_x])
// 		return (data->list = tmp, 1);
// 	if(data->list->current[tile_x] == '1')
// 		return (data->list = tmp, 1);
//     return (data->list = tmp, 0);
// }

void	draw_line(t_cub *data, int x, int y, float angle)
{
	int i = 0;
	int length = 100;
	while (i < length)
	{
		int xx = x + cos(angle) * i;
		int yy = y + sin(angle) * i;
		mlx_pixel_put(data->mlx, data->win, xx, yy, 0xD2042D);
		i++;
	}
}

void	my_pixel_put(t_cub *img, int x, int y, int color)
{
	int	offset;

	if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
		return;
	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(img->addr + offset)) = color;
}

void creat_wall(t_cub *data)
{
	int x = 0;
	int y = 0;
	t_list_line *tmp = data->list;
	int bra = 0;
	int ben = 0;

	while(tmp)
	{
		y = 0;
		while(tmp->current[y])
		{
			if(tmp->current[y] == '1')
			{
				ben = 0;
				while(ben < TILE_SIZE)
				{
					bra = 0;
					while(bra < TILE_SIZE)
						my_pixel_put(data, ((y * TILE_SIZE) + bra) * MINI_MAP, ((x * TILE_SIZE) + ben) * MINI_MAP, 0x3B38A0), bra++;
					ben++;
				}
			}
			else if(tmp->current[y] == '0' || tmp->current[y] == 'S' || tmp->current[y] == 'N'
					|| tmp->current[y] == 'E' || tmp->current[y] == 'W')
			{
				ben = 0;
				while(ben < TILE_SIZE)
				{
					bra = 0;
					while(bra < TILE_SIZE)
						my_pixel_put(data,  ((y * TILE_SIZE) + bra) * MINI_MAP, ((x * TILE_SIZE) + ben) * MINI_MAP, 0xF2EDD1), bra++;
					ben++;
				}
			}
			y++;
		}
		x++;
		tmp = tmp->next;
	}
}


int key_press(int keycode, void *player2)
{
	t_cub *player = (t_cub *)player2;
	
	if(keycode == 13)
		player->player.var.w = 1;
	if (keycode == 1)
		player->player.var.s = 1;
	if (keycode == 0)
		player->player.var.a = 1;
	if (keycode == 2)
		player->player.var.d = 1;
	if (keycode == 123)
		player->player.var.left = 1;
	if (keycode == 124)
		player->player.var.right = 1;
	if (keycode == 53)
	{
		mlx_destroy_image(player->mlx, player->img);
		mlx_destroy_window(player->mlx, player->win);
		free(player->textures.north);
		free(player->textures.south);
		free(player->textures.east);
		free(player->textures.west);
		ft_clear_list(&player->list);
		exit(0);
	}
	return (0);
}
int key_release(int keycode, void *player2)
{
	t_cub *player = (t_cub *)player2;
	
	if(keycode == 13)
		player->player.var.w = 0;
	if (keycode == 1)
		player->player.var.s = 0;
	if (keycode == 0)
		player->player.var.a = 0;
	if (keycode == 2)
		player->player.var.d = 0;
	if (keycode == 123)
		player->player.var.left = 0;
	if (keycode == 124)
		player->player.var.right = 0;
	return (0);
}

int update_player(t_cub *player)
{
	double new_x = player->player.pos_x;
	double new_y = player->player.pos_y;
	float move_steep = 10;

	if (player->player.var.w) // W
	{
		new_x += cos(player->player.angle) * move_steep;
		new_y += sin(player->player.angle) * move_steep;
		// printf("second == %f.....%f\n", new_x, new_y);
		// printf("second == %f.....\n", cos(player->player.angle));
	}
	if (player->player.var.s) // S
	{
		new_x -= cos(player->player.angle) * move_steep;
		new_y -= sin(player->player.angle) * move_steep;
		// printf("%f.....%f\n", new_x, new_y);
	}
	if (player->player.var.a) // A (Strafe left)
	{
		new_x += cos(player->player.angle - M_PI / 2) * move_steep;
		new_y += sin(player->player.angle - M_PI / 2) * move_steep;
		// printf("%f.....%f\n", new_x, new_y);
	}
	if (player->player.var.d) // D (Strafe right)
	{
		new_x += cos(player->player.angle + M_PI / 2) * move_steep;
		new_y += sin(player->player.angle + M_PI / 2) * move_steep;
		// printf("%f.....%f\n", new_x, new_y);
	}
	if (player->player.var.left)// <-
	{
		// printf("%d.....%d\n", new_x, new_y);
		player->player.angle -= 3 * (M_PI / 180);
		// printf("hhhhhhhhhh da3ti\n");
		// if (player->player.angle <= 0)
		// 	player->player.angle += 2 * M_PI; \\ to know if i need it 
		// ft_draw(player);
		// return (0);
	}
	if (player->player.var.right)// ->
	{
		player->player.angle += 3 * (M_PI / 180);
		// if (player->player.angle >= 2 * M_PI)
		// 	player->player.angle -= 2 * M_PI;
		// ft_draw(player);
		// return (0);
	}
	int size = 16;
	// int margin = 1;
	if (!is_wall(player, new_x - size, new_y - size) &&
		!is_wall(player, new_x + size, new_y - size) &&
		!is_wall(player, new_x - size, new_y + size) &&
		!is_wall(player, new_x + size, new_y + size))
	{
		player->player.pos_x = new_x;
		player->player.pos_y = new_y;
		// printf("talitan == %f.....%f\n", new_x, new_y);
	}
	return 0;
}

void normalize_angle(double *angle)
{
	*angle = fmod(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle += 2 * M_PI;
}

void fice_vision(t_cub *data)
{
	normalize_angle(&data->player.angle);
	if(data->player.angle > 0 && data->player.angle < M_PI)
		data->player.face_down = 1;
	else
		data->player.face_down = 0;
	data->player.face_up = !data->player.face_down;

	if (data->player.angle < M_PI / 2 || data->player.angle > 3 * M_PI / 2)
		data->player.face_right = 1;
	else
		data->player.face_right = 0;
	data->player.face_left = !data->player.face_right;
}


double ft_calcul_vitaghors(t_cub *data, double x, double y)
{
	return (sqrt((x - data->player.pos_x) * (x - data->player.pos_x)
				+ (y - data->player.pos_y) * (y - data->player.pos_y)));
}

double	for_cast(t_cub *data)
{

	// ******************************** horizontal *************************************
	bool wallhorz = false;
	data->player.inter_y = floor(data->player.pos_y / TILE_SIZE) * TILE_SIZE;
	if (data->player.face_down)
		data->player.inter_y += TILE_SIZE;
	// else
	// 	data->player.inter_y += 0.1;
	data->player.inter_x = data->player.pos_x + (data->player.inter_y - data->player.pos_y) / tan(data->player.angle);

	data->player.step_y = TILE_SIZE;
	if (data->player.face_up)
		data->player.step_y *= -1;

	data->player.step_x = TILE_SIZE / tan(data->player.angle);
	if (data->player.face_left && data->player.step_x > 0)
		data->player.step_x *= -1;
	if (data->player.face_right && data->player.step_x < 0)
		data->player.step_x *= -1;

	double x_horz = data->player.inter_x;
	double y_horz = data->player.inter_y;

	double wall_hit_x = 0;
	double wall_hit_y = 0;
	double tmp_y_horisontal = 0;
	while(x_horz >= 0 && x_horz <= data->size_x && y_horz >= 0 && y_horz <= data->size_y)
	{
		if (data->player.face_up)
			tmp_y_horisontal = y_horz - 1;
		else
			tmp_y_horisontal = y_horz;
		if (is_wall(data, x_horz, tmp_y_horisontal))
		{
			wallhorz = true;
			wall_hit_x = x_horz;
			wall_hit_y = y_horz;
			break ;
		}
		else
		{
			x_horz += data->player.step_x;
			y_horz += data->player.step_y;
		}
	}

	// ******************************** virtical *************************************

	bool wallvirtical = false;
	// bool wallhorz = false;
	data->player.inter_x = floor(data->player.pos_x / TILE_SIZE) * TILE_SIZE;
	if (data->player.face_right)
		data->player.inter_x += TILE_SIZE;
	// else
	// 	data->player.inter_x += 0.01;
	data->player.inter_y = data->player.pos_y + (data->player.inter_x - data->player.pos_x) * tan(data->player.angle);

	data->player.step_x = TILE_SIZE;
	if (data->player.face_left)
		data->player.step_x *= -1;
	
	data->player.step_y = TILE_SIZE * tan(data->player.angle);
	if (data->player.face_up && data->player.step_y > 0)
		data->player.step_y *= -1;
	if (data->player.face_down && data->player.step_y < 0)
		data->player.step_y *= -1;

	double x_virtical = data->player.inter_x;
	double y_virtical = data->player.inter_y;


	double wall_vir_x = 0; 
	double wall_vir_y = 0;
	double tmp_x_virtical = 0;

	while(x_virtical >= 0 && x_virtical <= data->size_x && y_virtical >= 0 && y_virtical <= data->size_y)
	{
		if (data->player.face_left)
			tmp_x_virtical = x_virtical - 1;
		else
			tmp_x_virtical = x_virtical;
		if (is_wall(data, tmp_x_virtical, y_virtical))
		{
			wallvirtical = true;
			wall_vir_x = x_virtical;
			wall_vir_y = y_virtical;
			break ;
		}
		else
		{
			x_virtical += data->player.step_x;
			y_virtical += data->player.step_y;
		}
	}

	double horisantal_distans = 0;
	double virtical_distans = 0;
	data->player.final_distans_closer_x = 0;
	data->player.final_distans_closer_y = 0;

	if(wallhorz)
		horisantal_distans = ft_calcul_vitaghors(data , wall_hit_x, wall_hit_y);
	else
		horisantal_distans = INT_MAX;
	if (wallvirtical)
		virtical_distans = ft_calcul_vitaghors(data, wall_vir_x, wall_vir_y);
	else 
		virtical_distans = INT_MAX;
	double final_distance = 0;
	// bool wasHitVertical;
	if(virtical_distans < horisantal_distans)
	{
		data->player.final_distans_closer_x = wall_vir_x;
		data->player.final_distans_closer_y = wall_vir_y;
		final_distance = virtical_distans;
		data->player.wasHitVertical = true;
	}
	else
	{
		data->player.final_distans_closer_x = wall_hit_x;
		data->player.final_distans_closer_y = wall_hit_y;
		final_distance = horisantal_distans;
		data->player.wasHitVertical = false;
	}
	// ********************** draw the ray *************************

	// double corner_of_player = 60 * (M_PI / 180);
	// double rotate = data->player.angle - (corner_of_player / 2);
	// // double rotate2 = data->player.angle + 30;
	// int y = 0;

	// while(y < 10)
	// {
	// 	// if(rotate > data->player.angle + (1.0472 / 2))
	// 	// 	break;
	// 	draw_line(data, data->player.pos_x + 16, data->player.pos_y + 16, rotate);
	// 	rotate += corner_of_player / 10;
	// 	y++;
	// }
	// int texture_x;
	// if (data->player.wasHitVertical)
	// 	texture_x = (int)fmod(final_distans_closer_y, TILE_SIZE) * data->textures.data[i].width / TILE_SIZE;
	// else
	// 	texture_x = (int)fmod(data->ray.hit_x, TILE_SIZE) * data->textures.data[i].width / TILE_SIZE;
		return (final_distance);
	// draw_line2(data->mlx, data->win, (data->player.pos_x + 16) * MINI_MAP,
	// 			(data->player.pos_y + 16) * MINI_MAP,
	// 				 final_distans_closer_x * MINI_MAP, final_distans_closer_y * MINI_MAP, 0xFF0000);
}


int	get_texture_data(t_textures *data, int x, int y, int i)
{
	int	offset;

	if (x < 0 || y < 0 || x >= data->data[i].width || y >= data->data[i].height)
		return -1;
	offset = (data->data[i].line_len * y) + (x * (data->data[i].bpp / 8));
	return *((unsigned int *)(data->data[i].addr + offset));
}

void get_data_for_images(t_cub *data)
{
	data->textures.data[0].data = mlx_xpm_file_to_image(data->mlx, data->textures.east,
								&data->textures.data[0].width, &data->textures.data[0].height);
	if(!data->textures.data[0].data)
		printf("error\n"), exit(0);
	data->textures.data[0].addr = mlx_get_data_addr(data->textures.data[0].data, &data->textures.data[0].bpp,
													&data->textures.data[0].line_len,
													&data->textures.data[0].endian);
									
	data->textures.data[1].data = mlx_xpm_file_to_image(data->mlx, data->textures.north,
								&data->textures.data[1].width, &data->textures.data[1].height);
	data->textures.data[1].addr = mlx_get_data_addr(data->textures.data[1].data, &data->textures.data[1].bpp,
													&data->textures.data[1].line_len,
													&data->textures.data[1].endian);
						

	data->textures.data[2].data = mlx_xpm_file_to_image(data->mlx, data->textures.south,
								&data->textures.data[2].width, &data->textures.data[2].height);
	data->textures.data[2].addr = mlx_get_data_addr(data->textures.data[2].data, &data->textures.data[2].bpp,
													&data->textures.data[2].line_len,
													&data->textures.data[2].endian);

	data->textures.data[3].data = mlx_xpm_file_to_image(data->mlx, data->textures.west,
								&data->textures.data[3].width, &data->textures.data[3].height);
	data->textures.data[3].addr = mlx_get_data_addr(data->textures.data[3].data, &data->textures.data[3].bpp,
													&data->textures.data[3].line_len,
													&data->textures.data[3].endian);
}

// void draw_vertical_wall_strip(t_cub *data, int x, int wall_top, int height)
// {
// 	int y = 0;
// 	int wall_bottom = wall_top + height;
	

// 	for (y = 0; y < WINDOW_HEIGHT; y++)
// 	{
// 		if (y < wall_top)
// 			my_pixel_put(data, x, y, data->colors.ceiling);
// 		else if (y >= wall_top && y <= wall_bottom)
// 		{
// 			if(data->player.face_left && data->player.wasHitVertical)
// 			{
// 				int texture_x;
// 				int texture_y;

// 				double step = (double)data->textures.data[3].height / height;
// 				double tex_pos = (y - wall_top) * step;
// 				texture_y = (int)tex_pos;
// 				if (data->player.wasHitVertical)
// 					texture_x = (int)fmod(data->player.final_distans_closer_y, TILE_SIZE) * data->textures.data[3].width / TILE_SIZE;
// 				else
// 					texture_x = (int)fmod(data->player.final_distans_closer_x, TILE_SIZE) * data->textures.data[3].width / TILE_SIZE;
// 				int color = get_texture_data(&data->textures, texture_x, texture_y, 3);
// 				// (void)color;
// 				my_pixel_put(data, x, y, color);
// 			}
// 			else if(data->player.face_right && data->player.wasHitVertical)
// 				my_pixel_put(data, x, y, 0xF58E27);
// 			else if(data->player.face_up && !data->player.wasHitVertical)
// 				my_pixel_put(data, x, y, 0xff0000);
// 			else if(data->player.face_down && !data->player.wasHitVertical)
// 				my_pixel_put(data, x, y, 0x301100F);
// 		}
// 		else
// 			my_pixel_put(data, x, y, data->colors.floor);
// 	}
// }
// void draw_vertical_wall_strip(t_cub *data, int x, int wall_top, int height)
// {
//     int y = 0;
//     int wall_bottom = wall_top + height;

// 	for (int i = 0; i < wall_top; i++)
//             my_pixel_put(data, x, y + i, data->colors.ceiling);
//     for (y = wall_top; y < wall_bottom; y++)
//     {
//         // if (y < wall_top)
//         //     my_pixel_put(data, x, y, data->colors.ceiling);
//         if (y >= wall_top && y <= wall_bottom)
//         {
//             if (data->player.face_left && data->player.wasHitVertical)
//             {
//                 int texture_x;
//                 int texture_y;
//                 double step = (double)data->textures.data[3].height / height;
//                 double tex_pos = (y - wall_top) * step;
//                 texture_y = (int)floor(tex_pos);
//                 if (texture_y >= data->textures.data[3].height)
//                     texture_y = data->textures.data[3].height - 1;

//                 texture_x = (int)((fmod(data->player.final_distans_closer_y, TILE_SIZE) / TILE_SIZE) * data->textures.data[3].width);
//                 int color = get_texture_data(&data->textures, texture_x, texture_y, 3);
//                 my_pixel_put(data, x, y, color);
//             }
//             else if (data->player.face_right && data->player.wasHitVertical)
// 			{
//                 int texture_x;
//                 int texture_y;
//                 double step = (double)data->textures.data[1].height / height;
//                 double tex_pos = (y - wall_top) * step;
//                 texture_y = (int)floor(tex_pos);
//                 if (texture_y >= data->textures.data[1].height)
//                     texture_y = data->textures.data[1].height - 1;

//                 texture_x = (int)((fmod(data->player.final_distans_closer_y, TILE_SIZE) / TILE_SIZE) * data->textures.data[1].width);
//                 int color = get_texture_data(&data->textures, texture_x, texture_y, 1);
//                 my_pixel_put(data, x, y, color);
// 			}
//             else if (data->player.face_up && !data->player.wasHitVertical)
// 			{
//                 int texture_x;
//                 int texture_y;
//                 double step = (double)data->textures.data[2].height / height;
//                 double tex_pos = (y - wall_top) * step;
//                 texture_y = (int)floor(tex_pos);
//                 if (texture_y >= data->textures.data[2].height)
//                     texture_y = data->textures.data[2].height - 1;

//                 texture_x = (int)((fmod(data->player.final_distans_closer_x, TILE_SIZE) / TILE_SIZE) * data->textures.data[2].width);
//                 int color = get_texture_data(&data->textures, texture_x, texture_y, 2);
//                 my_pixel_put(data, x, y, color);
//                 // my_pixel_put(data, x, y, 0xff0000);
// 			}
//             else if (data->player.face_down && !data->player.wasHitVertical)
// 			{
//                 int texture_x;
//                 int texture_y;
//                 double step = (double)data->textures.data[0].height / height;
//                 double tex_pos = (y - wall_top) * step;
//                 texture_y = (int)floor(tex_pos);
//                 if (texture_y >= data->textures.data[0].height)
//                     texture_y = data->textures.data[0].height - 1;

//                 texture_x = (int)((fmod(data->player.final_distans_closer_x, TILE_SIZE) / TILE_SIZE) * data->textures.data[0].width);
//                 int color = get_texture_data(&data->textures, texture_x, texture_y, 0);
//                 my_pixel_put(data, x, y, color);
//                 // my_pixel_put(data, x, y, 0x301100F);
// 			}
//         }
//     }
//         for (y = wall_bottom; y < WINDOW_HEIGHT; y++)
//             my_pixel_put(data, x, y, data->colors.floor);
// }


void draw_vertical_wall_strip(t_cub *data, int x, int wall_top, int height)
{
    int y;
    int wall_bottom = wall_top + height;

    for (y = 0; y < wall_top; y++)
        my_pixel_put(data, x, y, data->colors.ceiling);

    for (y = wall_top; y < wall_bottom && y < WINDOW_HEIGHT; y++)
    {
        int texture_x, texture_y;
        double step;
        double tex_pos;
        int tex_index;

        if (data->player.wasHitVertical)
        {
            if (data->player.face_left)
                tex_index = 3;
            else
                tex_index = 0;

            texture_x = (int)((fmod(data->player.final_distans_closer_y, TILE_SIZE) / TILE_SIZE) * data->textures.data[tex_index].width);
        }
        else
        {
            if (data->player.face_up)
                tex_index = 1;
            else
                tex_index = 2;

            texture_x = (int)((fmod(data->player.final_distans_closer_x, TILE_SIZE) / TILE_SIZE) * data->textures.data[tex_index].width);
        }
        step = (double)data->textures.data[tex_index].height / height;
        tex_pos = (y - wall_top) * step;
        texture_y = (int)floor(tex_pos);

        if (texture_y >= data->textures.data[tex_index].height)
            texture_y = data->textures.data[tex_index].height - 1;

        int color = get_texture_data(&data->textures, texture_x, texture_y, tex_index);
        my_pixel_put(data, x, y, color);
    }

    for (y = wall_bottom; y < WINDOW_HEIGHT; y++)
        my_pixel_put(data, x, y, data->colors.floor);
}

// void draw_vertical_wall_strip(t_cub *data, int x, int wall_top, int height, double ray_distance, double ray_angle)
// {
//     int y = 0;
//     int wall_bottom = wall_top + height;
//     double corrected_distance = ray_distance * cos(ray_angle - data->player.angle);
//     if (corrected_distance <= 0)
//         corrected_distance = 0.0001;

//     for (y = 0; y < WINDOW_HEIGHT; y++)
//     {
//         if (y < wall_top)
//             my_pixel_put(data, x, y, data->colors.ceiling);
//         else if (y >= wall_top && y <= wall_bottom)
//         {
//             if (data->player.face_left && data->player.wasHitVertical)
//             {
//                 int texture_x;
//                 int texture_y;
//                 double step = (double)data->textures.data[3].height / height;
//                 double tex_pos = (y - wall_top) * step;
//                 texture_y = (int)floor(tex_pos);
//                 if (texture_y >= data->textures.data[3].height)
//                     texture_y = data->textures.data[3].height - 1;

//                 texture_x = (int)((fmod(data->player.final_distans_closer_y, TILE_SIZE) / TILE_SIZE) * data->textures.data[3].width);
//                 int color = get_texture_data(&data->textures, texture_x, texture_y, 3);
//                 my_pixel_put(data, x, y, color);
//             }
//             else if (data->player.face_right && data->player.wasHitVertical)
//                 my_pixel_put(data, x, y, 0xF58E27);
//             else if (data->player.face_up && !data->player.wasHitVertical)
//                 my_pixel_put(data, x, y, 0xff0000);
//             else if (data->player.face_down && !data->player.wasHitVertical)
//                 my_pixel_put(data, x, y, 0x301100F);
//         }
//         else
//             my_pixel_put(data, x, y, data->colors.floor);
//     }
// }

void rendring_wall_s(t_cub *data)
{
	// double corner_of_player = FOV_ANGLE;
	double start_angle = data->player.angle - (FOV_ANGLE / 2);
	int i = 0;

	double distanceProjectionPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	
	// get_data_for_images(data);
	
	////////////////// FOV = Field of View
	
	while (i < NUM_RAYS)
	{
		double ray_angle = start_angle + i * (FOV_ANGLE / NUM_RAYS);
		double old_angle = data->player.angle;
		data->player.angle = ray_angle;

		fice_vision(data);

		double ray_distance = for_cast(data);

		data->player.angle = old_angle;

		double corrected_distance = ray_distance * cos(ray_angle - old_angle);
		// printf(" corrected_distance === %f ||||||||||   ray_distance ==== %f\n", corrected_distance, distanceProjectionPlane);
		if (corrected_distance <= 0)
			printf("asdfljasdljasd;ljasd;ljasdf;lajsdf;lkasjdfl;aksjf;alksdjfa;djklsfa;sdf\n"), exit(0), corrected_distance = 0.0001;
		// printf("i ==== %d >>>>    corrected_destance ====== %f\n", i, corrected_distance);

		////////////////// Similar triangles
		int wall_strip_height = (int)((TILE_SIZE / corrected_distance) * distanceProjectionPlane);

		int wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
		// printf("%d\n", )
		draw_vertical_wall_strip(data, i * WALL_STRIP_WIDTH, wall_top_pixel, wall_strip_height);

		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

#define MINIMAP_SIZE 200


void draw_rectangle(t_cub *data, int x, int y, int width, int height, int color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			my_pixel_put(data, x + i, y + j, color);
		}
	}
}
void miniMap(t_cub *data)
{
	double minimap_scale = (double)MINIMAP_SIZE / (double)(data->colum * TILE_SIZE);
	double offset_x = data->player.pos_x * minimap_scale - MINIMAP_SIZE / 2;
	double offset_y = data->player.pos_y * minimap_scale - MINIMAP_SIZE / 2;
	
	for (int y = 0; y < data->row; y++) {
		for (int x = 0; x < data->colum; x++) {
			if (is_wall(data, x, y)) {
				int draw_x = x * TILE_SIZE * minimap_scale - offset_x;
				int draw_y = y * TILE_SIZE * minimap_scale - offset_y;
				draw_rectangle(data, draw_x, draw_y, TILE_SIZE*minimap_scale, TILE_SIZE*minimap_scale, 0X702963);
			}
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}


int ft_draw(t_cub *data)
{
	// updata_for_xy(data);
	// clear_image(data);
	// creat_wall(data);
	update_player(data);
	// printf("x .. %f...... y .. %f\n", data->player.pos_x, data->player.pos_y);
	// int ls = 0;
	// int ls2 = 0;
	mlx_clear_window(data->mlx, data->win);
	// void *brahim = mlx_xpm_file_to_image(data->mlx_connection, "istockphoto-547528110-612x612.xpm", &ls , &ls);
	// mlx_put_image_to_window(data->mlx_connection,data->mlx_windows, brahim, WIDTH, HEIGHT);
	rendring_wall_s(data);
	// miniMap(data);
	// creat_wall(data);
	// draw(data->player.y, data->player.x, 25, 0xFF0000,data);
	// void *mlls = mlx_xpm_file_to_image(data->mlx, "arow.xpm", &ls, &ls2);
	// mlx_put_image_to_window(data->mlx, data->win, mlls, 0.2 * (data->player.pos_x),
	// 	0.2 * (data->player.pos_y));
	
	// while(ls < 32)
	// {
	// 	ls2 = 0;
	// 	while(ls2 < 32)
	// 	{
	// 		my_pixel_put(data, ((data->player.pos_x - 16) + ls2) * MINI_MAP,
	// 			((data->player.pos_y - 16) + ls) * MINI_MAP, 0x00ff00);
	// 		ls2++;
	// 	}
	// 	ls++;
	// }
	// mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	// draw_line(data, data->player.pos_x + 16, data->player.pos_y + 16, data->player.angle);
	// for_ray_casting2(data);
	// draw_line(data, data->player.pos_x + 16, data->player.pos_y + 16, data->player.angle);
	// mlx_put_image_to_window(data->mlx_connection, data->mlx_windows, data->mlx_image, 0 , 0);
	return (0);
}

void f()
{
	system("leaks cub3D");
}
char **ft_convert_list(t_list_line *list)
{
	char **map;
	int i = 0;
	int j = 0;
	int len = 0;
	t_list_line *tmp = list;


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
	while (list)
	{
		map[j]= ft_strdup(list->current);
		if (!map[j])
		{
			while (i < j)
				free(map[i++]);
			free(map);
			return (NULL);
		}
		j++;
		list = list->next;
	}
	map[j] = NULL;
	list = tmp;
	return (map);
}

int	main(int ac, char **av)
{
	t_cub	game;
	int		fd;
	int		sort;

	// atexit(f);
	if (ac != 2)
		return (ft_putendl_fd("Usage: ./cub3D <path/to/map.cub>", 2), 1);
	init_texture(&game);
	fd = ft_open_map(av[1]);
	if (fd == -1)
		return (1);
	sort = ft_config_map(fd, &game);
	if (sort != 0)
		return (sort);
	count_map(&game);
	game.grind = ft_convert_list(game.list);
	if (!game.grind)
		return (ft_putendl_fd("Error: Failed to convert list to map or allocation", 2), 1);
	if (ft_init_cub(&game) == -1)
		 (ft_putendl_fd("error in mlx", 2), exit(1));
		get_data_for_images(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	//ft_build_2d_map(&game);
	mlx_hook(game.win, 17, 1L << 17, ft_close, &game.mlx);
	mlx_loop_hook(game.mlx, ft_draw, &game);
	// mlx_key_hook(game.win, ft_esc_close, &game.mlx);
	mlx_loop(game.mlx);
}
