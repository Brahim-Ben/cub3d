/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:00:45 by slimane           #+#    #+#             */
/*   Updated: 2025/09/20 09:47:10 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include <string.h>

# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2005
# endif

# define NUM_FRAMES 11
# define TILE_SIZE 64
# define WINDOW_WIDTH 1192
# define WINDOW_HEIGHT 1192
# define FOV_ANGLE 1.0472
# define NUM_RAYS WINDOW_WIDTH

typedef struct s_list_line
{
	char				*current;
	struct s_list_line	*next;
}						t_list_line;

typedef struct s_data_text
{
	int		height;
	int		width;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	void	*data;
}			t_data_text;

typedef struct s_var_for_cast
{
	double	hit_x;
	double	hit_y;
	double	vhit_x;
	double	vhit_y;
	double	hdist;
	double	vdist;
}	t_var_for_cast;

typedef struct s_rendring_animation
{
	int	frame;
	int	start_x;
	int	start_y;
	int	y;
	int	x;
	int	color;
}	t_rendring_animation;

typedef struct s_update_player
{
	double	new_x;
	double	new_y;
	float	move_step;
	int		margin;
}	t_update_player;

typedef struct data_for_wall
{
	int	height_wall;
	int	wall_bottom;
	int	wall_top;
}	t_data_for_wall;
typedef struct s_var_draw_wall
{
	int		y;
	int		texture_y;
	int		color;
	int		texture_x;
	double	step;
	double	tex_pos;
	int		tex_index;
}	t_var_draw_wall;

typedef struct s_variables
{
	double	start_angle;
	double	distanceprojectionplane;
	double	old_angle;
	double	ray_distance;
	double	corrected_distance;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		i;
}	t_variables;

typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	t_data_text	data[4];
	int			texture_y;
	int			texture_x;
}				t_textures;

typedef struct s_colors
{
	int	floor;
	int	ceiling;
}		t_colors;

typedef struct s_move
{
	int	w;
	int	s;
	int	a;
	int	d;

	int	left;
	int	right;
}	t_move;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	face_down;
	double	face_up;
	double	face_right;
	double	face_left;
	double	inter_x;
	double	inter_y;
	double	step_x;
	double	step_y;
	double	final_distans_closer_x;
	double	final_distans_closer_y;
	t_move	var;
	double	angle;
	bool	washitvertical;
}			t_player;

typedef struct s_animation
{
	int			height;
	int			width;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	void		*data;
}				t_animation;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			config_count;
	int			map_started;
	int			size_x;
	int			size_y;
	int			row;
	int			colum;
	char		**grind;
	int			last_x;
	int			fd;
	t_animation	anime[11];
	t_textures	textures;
	t_colors	colors;
	t_player	player;
	t_list_line	*list;
}				t_cub;

void	ft_putendl_fd(char *str, int fd);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
void	ft_destroy_mlx(t_cub *cub);
char	*ft_strdup(const char *s1);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
int		ft_config_map(int fd, t_cub *map);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_free(char **strs, int count);
char	*ft_strtrim(char const *s1, char const *set);
int		parse_the_map(t_cub *cub, t_list_line *list);
char	*find_new_line(char *s);
int		is_just_space(char *line);
void	*lst_addback(t_list_line **list, char *line);
int		lst_size(t_list_line *list);
void	ft_clear_list(t_list_line **list);
void	fr_text(t_cub *cub);
int		ft_init_cub(t_cub *cub);
int		ft_init_mlx(t_cub *mlx);
void	init_texture(t_cub *cub);
int		ft_atoi(const char *str);
int		ft_convert_hex(char *str);
int		ft_strlen2(char *str);
int		ft_isdigit(int c);
int		ft_check_something_else(char *strs);
int		ft_mini_check(t_cub *cub, char *trim, int flag, int i);
int		ft__second_mini_check(t_cub *cub, char *trim, int flag, int i);
int		check_min_textute(t_cub *cub, char *tmp, char *trim, int i);
int		ft_check_colors(char *tmp, char *trim, t_cub *cub, int i);
int		check_north(t_list_line *prev, int i);
int		check_south(t_list_line *next, int i);
int		check_east(t_list_line *curr, int i);
int		check_west(t_list_line *curr, int i);
double	for_cast(t_cub *data);
double	ft_calcul_vitaghors(t_cub *data, double x, double y);
int		is_wall(t_cub *data, double x, double y);
void	draw_vertical_wall_strip(t_cub *data, int x, int wall_top,
			int height_wall);
int		get_texture_pixel(t_textures *data, int x, int y, int i);
void	my_pixel_put(t_cub *img, int x, int y, int color);
void	ft_destroy_imag_textes(t_cub *data);
int		ft_open_map(char *str);
int		ft_close(t_cub *mlx);
int		check_pos_player(char c, t_cub *data);
void	declared(t_cub *game);
void	count_map(t_cub *game);
void	normalize_angle(double *angle);
void	update_player(t_cub *player);
int		key_press(int keycode, void *player2);
int		key_release(int keycode, void *player2);
void	rendring_wall_s(t_cub *data);
char	**ft_convert_list(t_list_line *list);
int		ft_draw(t_cub *data);
int		get_data_for_images(t_cub *data);
#endif