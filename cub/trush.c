// int	ft_esc_close(int btn, t_cub	*mlx)
// {
// 	if (btn == 53)
// 	{
// 		mlx_destroy_image(mlx->mlx, mlx->img);
// 		mlx_destroy_window(mlx->mlx, mlx->win);
// 		free(mlx->textures.north);
// 		free(mlx->textures.south);
// 		free(mlx->textures.east);
// 		free(mlx->textures.west);
// 		ft_clear_list(&mlx->list);
// 		exit(0);
// 	}
// 	return (0);
// }

// int ft_check_emty_node(t_list_line *game)
// {
// 	int	i;

// 	i = 0;
// 	// if(game->current[i] == '\0')
// 	// 	return (1);
// 	while(game->current[i])
// 	{
// 		if(game->current[i] != ' ')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }




// int is_wall(t_cub *data, int x, int y)
// {
//     int tile_x = x / 64;
//     int tile_y = y / 64;
//     int i = 0;
//     t_list_line *tmp = data->list;

//     if (data->player.face_up && y > 0)
//         y--, tile_y = y / 64;

//     while (i < tile_y && data->list)
//     {
//         data->list = data->list->next;
//         i++;
//     }
//     if (!data->list)
//         return (data->list = tmp, 1);


//     if (tile_x >= (int)strlen(data->list->current) || tile_x < 0)
//         return (data->list = tmp, 1);

//     if (data->list->current[tile_x] == '1')
//         return (data->list = tmp, 1);

//     return (data->list = tmp, 0);
// }




// void draw_line2(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color)
// {
// 	double dx = x2 - x1;
// 	double dy = y2 - y1;

// 	double steps = fmax(fabs(dx), fabs(dy));
// 	double x_inc = dx / steps;
// 	double y_inc = dy / steps;

// 	double x = x1;
// 	double y = y1;

// 	for (int i = 0; i <= steps; i++)
// 	{
// 		mlx_pixel_put(mlx_ptr, win_ptr, round(x), round(y), color);
// 		x += x_inc;
// 		y += y_inc;
// 	}
// }





























	/*
		DDA: digital differential analyzer.

		Ay = floor(point_y_of_player/size_of_the_squer) * size_of_the_squer
		Ax = Px + (Py - Ay)/tan(alpha).
		
		** أفقي
		ystep = size_of_the_squer.
		xstep = size_of_the_squer / tan(alpha).
			
			
			video 5.
		* عمودي
		xstep = size_of_the_squer.
		ystep = size_of_the_squer * tan(alpha).


		==> Rendering Walls:
			-> first rule: 
				TILE_SIZE/Ray_distance = projected wall height/distance from player to proj.plane.
			
			distnaceProjPlane = (WINDOW_WIDTH/2) / tan(FOV_ANGLE / 2);
			wallstripHeight = (TILE_SIZE/Ray_distance) * distance from player to proj.plane(diestanceProjPlane);
	*/









			// printf("%f\n", x_horz);
			// draw_line(data, wall_hit_x, wall_hit_y , data->player.angle);
			// draw_line2(data->mlx, data->win, data->player.pos_x + 16, data->player.pos_y + 16, wall_hit_x, wall_hit_y, 0xFF0000);

























            // double for_cast(t_cub *data)
// {
//     bool wallhorz = false;
//     bool wallvert = false;

//     // Horizontal intersection
//     data->player.inter_y = floor(data->player.pos_y / 64) * 64;
//     if (data->player.face_down)
//         data->player.inter_y += 64;
//     data->player.inter_x = data->player.pos_x + (data->player.inter_y - data->player.pos_y) / tan(data->player.angle);

//     data->player.step_y = 64;
//     if (data->player.face_up)
//         data->player.step_y *= -1;
//     data->player.step_x = 64 / tan(data->player.angle);
//     if (data->player.face_left && data->player.step_x > 0)
//         data->player.step_x *= -1;
//     if (data->player.face_right && data->player.step_x < 0)
//         data->player.step_x *= -1;

//     double x_horz = data->player.inter_x;
//     double y_horz = data->player.inter_y;
//     double wall_hit_x = 0;
//     double wall_hit_y = 0;

//     while (x_horz >= 0 && x_horz <= data->size_x && y_horz >= 0 && y_horz <= data->size_y)
//     {
//         double check_y = data->player.face_up ? y_horz - 1 : y_horz;
//         if (is_wall(data, x_horz, check_y))
//         {
//             wallhorz = true;
//             wall_hit_x = x_horz;
//             wall_hit_y = y_horz;
//             break;
//         }
//         x_horz += data->player.step_x;
//         y_horz += data->player.step_y;
//     }

//     // Vertical intersection
//     data->player.inter_x = floor(data->player.pos_x / 64) * 64;
//     if (data->player.face_right)
//         data->player.inter_x += 64;
//     data->player.inter_y = data->player.pos_y + (data->player.inter_x - data->player.pos_x) * tan(data->player.angle);

//     data->player.step_x = 64;
//     if (data->player.face_left)
//         data->player.step_x *= -1;
//     data->player.step_y = 64 * tan(data->player.angle);
//     if (data->player.face_up && data->player.step_y > 0)
//         data->player.step_y *= -1;
//     if (data->player.face_down && data->player.step_y < 0)
//         data->player.step_y *= -1;

//     double x_vert = data->player.inter_x;
//     double y_vert = data->player.inter_y;
//     double wall_vert_x = 0;
//     double wall_vert_y = 0;

//     while (x_vert >= 0 && x_vert <= data->size_x && y_vert >= 0 && y_vert <= data->size_y)
//     {
//         double check_x = data->player.face_left ? x_vert - 1 : x_vert;
//         if (is_wall(data, check_x, y_vert))
//         {
//             wallvert = true;
//             wall_vert_x = x_vert;
//             wall_vert_y = y_vert;
//             break;
//         }
//         x_vert += data->player.step_x;
//         y_vert += data->player.step_y;
//     }

//     double horz_dist = wallhorz ? ft_calcul_vitaghors(data, wall_hit_x, wall_hit_y) : INFINITY;
//     double vert_dist = wallvert ? ft_calcul_vitaghors(data, wall_vert_x, wall_vert_y) : INFINITY;
//     double final_distance;
//     double final_distans_closer_x;
//     double final_distans_closer_y;

//     if (vert_dist < horz_dist)
//     {
//         final_distans_closer_x = wall_vert_x;
//         final_distans_closer_y = wall_vert_y;
//         final_distance = sqrt(vert_dist);
//     }
//     else
//     {
//         final_distans_closer_x = wall_hit_x;
//         final_distans_closer_y = wall_hit_y;
//         final_distance = sqrt(horz_dist);
//     }

//     return final_distance;
// }






// void for_ray_casting2(t_cub *data)
// {
// 	double corner_of_player = 60 * (M_PI / 180);
// 	double start_angle = data->player.angle - (corner_of_player / 2);
// 	int i = 0;
// 	double ray_angle;

// 	while (i < NUM_RAYS)
// 	{
// 		ray_angle = start_angle + i * (corner_of_player / NUM_RAYS);

// 		double old_angle = data->player.angle;
// 		data->player.angle = ray_angle;
// 		fice_vision(data);
// 		for_cast(data);
// 		data->player.angle = old_angle;
// 		i++;
// 	}
// }


// void for_ray_casting(t_cub *data)
// {

// 	double corner_of_player = 60 * (M_PI / 180);
// 	data->player.angle = data->player.angle - (corner_of_player / 2);
// 	// double rotate2 = data->player.angle + 30;
// 	int y = 0;
	
// 	while(y < 10)
// 	{
// 		printf("adsfafadsfasdfasfdsfasfasdfasdfasfasdfasdf\n");
// 		// if(rotate > data->player.angle + (1.0472 / 2))
// 		// 	break;
// 		// draw_line(data, data->player.pos_x + 16, data->player.pos_y + 16, data->player.angle);
// 		fice_vision(data);
// 		for_cast(data);
// 		printf("%d\n", y);
// 		data->player.angle += corner_of_player / 10;
// 		y++;
// 	}
// }


// void draw_vertical_wall_strip(t_cub *data, int x, int y, int width, int height)
// {
//     int i, j;
//     for (j = y; j < y + height; j++)
//     {
//         for (i = 0; i < width; i++)
//         {
//             if (j >= 0 && j < WINDOW_HEIGHT && x + i >= 0 && x + i < WINDOW_WIDTH)
//             {
//                 my_pixel_put(data, x + i, j, 0xE43636);
//             }
//         }
//     }
// }


























// int key_ press(int keycode, void *player2)
// {
//     t_cub *player = (t_cub *)player2;
//     int new_x = player->player.pos_x;
//     int new_y = player->player.pos_y;
//     int size = 32;

//     if (keycode == 13) // W
//         new_y -= 10;
//     if (keycode == 1) // S
//         new_y += 10;
//     if (keycode == 0) // A
//         new_x -= 10;
//     if (keycode == 2) // D
//         new_x += 10;
// 	if (keycode == 123)
// 	{
// 		player->player.angle -= 0.1;
// 		if (player->player.angle < 0)
// 			player->player.angle += 2 * M_PI;
// 		ft_draw(player);
// 		return (0);
// 	}
// 	if (keycode == 124)
// 	{
// 		player->player.angle += 0.1;
// 		if (player->player.angle >= 2 * M_PI)
// 			player->player.angle -= 2 * M_PI;
// 		ft_draw(player);
// 		return (0);
// 	}
//     if (!is_wall(player, new_x, new_y) &&
//         !is_wall(player, new_x + size - 2, new_y) &&
//         !is_wall(player, new_x, new_y + size - 2)  &&
//         !is_wall(player, new_x + size - 2, new_y + size - 2))
//     {
//         player->player.pos_x = new_x;
//         player->player.pos_y = new_y;
//     }
//     return 0;
// }