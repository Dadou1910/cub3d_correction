/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:01:59 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 13:20:09 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../Libft/libft.h"
# include "../minilib/mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define WIDTH 1280
# define HEIGHT 720
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define TILE_SIZE 64
# define FOV 0.66
# define ROTATION_SPEED 0.02
# define MOVE_SPEED 0.05
# define MINIMAP_SIZE 150
# define TILE_SIZE_MINI 10
# define PLAYER_SIZE 4

typedef struct s_temp
{
	double		step;
	double		texpos;
	int			texx;
	int			texy;
	int			color;
	int			side;
}				t_temp;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}				t_texture;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_texture	north_texture;
	t_texture	south_texture;
	t_texture	east_texture;
	t_texture	west_texture;
	int			floor_color;
	int			ceiling_color;
}				t_mlx;

typedef struct s_ray
{
	double		raydirx;
	double		raydiry;
	double		deltadistx;
	double		deltadisty;
	double		sidedistx;
	double		sidedisty;
	double		camerax;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
}				t_ray;

typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
}				t_keys;

typedef struct s_minmap
{
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
}				t_minmap;

typedef struct s_game
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		angle;
	int			currentstripe;
	int			map_width;
	int			map_height;
	int			count[6];
	char		**map;
	int			init;
	char		*buffer;
	int			drawstart;
	int			drawend;
	int			map_started;
	int			touches_border;
	char		**temp_map;
	t_keys		keys;
	t_mlx		*mlx;
	t_ray		ray;
	t_minmap	minmap;
}				t_game;

//===================================================================//
//					  		 EXEC								 //
//===================================================================//

int			close_window(void *param);
int			key_press(int keycode, t_game *game);
void		init_game(t_game *game, t_mlx *mlx);
void		init_mlx(t_game *game, t_mlx *mlx);
void		init_ray(t_ray ray);
void		init_temp(t_temp temp);
void		init_minmap(t_game *game);
void		rotate_player(t_game *game, double rotationspeed);
void		move_player(t_game *game, double movespeed);
void		key_events(t_game *game, t_mlx *mlx);
void		compute_ray_properties(t_game *game, t_ray *ray);
void		calculate_side_dist(t_game *game, t_ray *ray);
void		calculate_ray_direction(t_game *game, t_ray *ray);
void		process_raycasting(t_game *game, t_ray *ray, t_mlx *mlx);
void		render_frame(t_game *game, t_ray *ray, char **map, t_mlx *mlx);
void		render_textured_column(t_game *game, int x, int side, double wallx);
void		my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void		clear_screen(t_mlx *mlx);
void		calculate_map_dimensions(t_game *game);
void		draw_tile(t_mlx *mlx, int x, int y, int color);
void		init_mlx_null(t_mlx *mlx);
char		*get_next_line(int fd, t_game *game);

//===================================================================//
//					  		 PARSING   							 //
//===================================================================//

int			parse_color(t_game *game, char *line, char *li);
int			help_walls(t_game *game, int x, int y);
int			is_valid_map_char(char c);
void		validate_config(t_mlx *mlx);
char		*trim_whitespace(char *str);
int			check_text(char *line);
void		free_map(char **map);
int			is_surrounded_by_walls(t_game *game);
int			is_valid_color(int color, const char *type);
int			is_valid_cub_file(const char *filename);
void		check_malloc(t_game *game, t_mlx *mlx);
void		load_texture(t_mlx *mlx, t_texture *texture, t_game *game,
				char *path);
int			check_duplicate_or_missing(t_game *game, t_mlx *mlx);
void		parse_file(const char *filename, t_game *game, t_mlx *mlx);
void		parse_config(char *line, char *li, t_game *game);
void		helper_surrounded(t_game *game, int x, int y);
void		validate_map(t_game *game);
void		help_dimension(t_game *game, char c);
void		clean_exit(t_game *game, t_mlx *mlx);
void		cleanup_and_exit(t_game *game, t_mlx *mlx, const char *error_msg);
void		validate_config_map(char *line, t_game *game, t_mlx *mlx);
void		validate_accessible_map(t_game *game);
void		set_player_orientation(t_game *game, char orientation);
void		flood_fill(char **map, int x, int y, t_game *game);
void		flood_fill2(char **map, int x, int y, t_game *game);
t_texture	*select_texture(t_game *game, t_mlx *mlx, int side);
#endif