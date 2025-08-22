/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brahim.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:00:45 by slimane           #+#    #+#             */
/*   Updated: 2025/08/21 17:49:44 by bbenaali         ###   ########.fr       */
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
#include <math.h>
#include <string.h>

#include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2005
# endif

# define MINI_MAP 0.2



/*****************************/

#define TILE_SIZE 64
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1200
#define FOV_ANGLE (60 * (M_PI / 180))
#define WALL_STRIP_WIDTH 1
#define NUM_RAYS (WINDOW_WIDTH / WALL_STRIP_WIDTH)

/*****************************/


typedef struct s_list_line
{
	char				*current;
	struct s_list_line	*next;
}						t_list_line;

typedef struct s_data_text
{
	int height;
	int width;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	void *data;
	// void *south_data;
	// void *west_data;
	// void *east_data;
}	t_data_text;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;

	t_data_text data[4];
	int	texture_y;
	int texture_x;
	// int height[4];
	// int width[4];
	// char		*addr;
	// int			bpp;
	// int			line_len;
	// int			endian;
	// void *north_data;
	// void *south_data;
	// void *west_data;
	// void *east_data;
}			t_textures;

typedef struct s_colors
{
	int	floor;
	int	ceiling;
}		t_colors;

typedef struct s_move
{
	int w;
	int s;
	int a;
	int d;

	int left;
	int right;
} t_move;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double face_down;
	double face_up;
	double face_right;
	double face_left;
	double	inter_x;
	double	inter_y;
	double	step_x;
	double	step_y;
	double	final_distans_closer_x;
	double	final_distans_closer_y;
	t_move  var;
	// int		spawn_count;
	// char	initial_dir_char;
	double	angle;
	//     void *brahim;
    // void *mlx_imagess;
	bool wasHitVertical;
} t_player;


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
	int 		colum;
	char        **grind;
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
void	ft_free_texture(t_cub *cub);
// char	*ft_itoa(int n);
int		ft_init_cub(t_cub *cub);
int		ft_init_mlx(t_cub *mlx);
void	init_texture(t_cub *cub);
int		ft_atoi(const char *str);
int		ft_convert_hex(char *str);
int		ft_strlen2(char *str);
// void    ft_build_2d_map(t_cub *cub);

#endif