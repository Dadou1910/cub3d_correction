/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 13:26:05 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_player(t_game *game, t_mlx *mlx, t_minmap minmap)
{
	int	player_screen_y;
	int	i;
	int	j;
	int	px;
	int	py;

	i = -PLAYER_SIZE;
	player_screen_y = (game->posy - minmap.start_y) * TILE_SIZE_MINI;
	while (i <= PLAYER_SIZE)
	{
		j = -PLAYER_SIZE;
		while (j <= PLAYER_SIZE)
		{
			px = ((game->posx - minmap.start_x) * TILE_SIZE_MINI) + i;
			py = player_screen_y + j;
			if (px >= 0 && px < MINIMAP_SIZE && py >= 0 && py < MINIMAP_SIZE)
				my_mlx_pixel_put(mlx, px, py, 0xD98085);
			j++;
		}
		i++;
	}
}

void	draw_direction_line(t_game *game, t_mlx *mlx, t_minmap minmap)
{
	int	player_screen_y;
	int	line_length;
	int	i;
	int	line_x;
	int	line_y;

	i = 0;
	line_length = 14;
	player_screen_y = (game->posy - minmap.start_y) * TILE_SIZE_MINI;
	while (i < line_length)
	{
		line_x = ((game->posx - minmap.start_x) * TILE_SIZE_MINI)
			+ (int)(game->dirx * i);
		line_y = player_screen_y + (int)(game->diry * i);
		if (line_x >= 0 && line_x < MINIMAP_SIZE
			&& line_y >= 0 && line_y < MINIMAP_SIZE)
			my_mlx_pixel_put(mlx, line_x, line_y, 0xD98085);
		i++;
	}
}

void	render_minimap_viewport(t_game *game, t_mlx *mlx, t_minmap minmap)
{
	int	y;
	int	x;
	int	color;
	int	screen_x;
	int	screen_y;

	y = minmap.start_y;
	while (y < minmap.end_y)
	{
		x = minmap.start_x;
		while (x < minmap.end_x)
		{
			color = 0xE6E6FA;
			if (game->map[y][x] == '1')
				color = 0xFFD1DC;
			else if (game->map[y][x] == '0')
				color = 0xFFB6C1;
			screen_x = (x - minmap.start_x) * TILE_SIZE_MINI;
			screen_y = (y - minmap.start_y) * TILE_SIZE_MINI;
			draw_tile(mlx, screen_x, screen_y, color);
			x++;
		}
		y++;
	}
}

void	helper_minimap(int game_param, int *end, int *start)
{
	if (*end > game_param)
	{
		*start = game_param - MINIMAP_SIZE / TILE_SIZE_MINI;
		*end = game_param;
	}
}

void	render_minimap(t_game *game, t_mlx *mlx)
{
	t_minmap	minmap;

	minmap = minmap;
	init_minmap(game);
	minmap.start_x = (int)game->posx - MINIMAP_SIZE / (2 * TILE_SIZE_MINI);
	minmap.start_y = (int)game->posy - MINIMAP_SIZE / (2 * TILE_SIZE_MINI);
	if (minmap.start_x < 0)
		minmap.start_x = 0;
	if (minmap.start_y < 0)
		minmap.start_y = 0;
	minmap.end_x = minmap.start_x + MINIMAP_SIZE / TILE_SIZE_MINI;
	minmap.end_y = minmap.start_y + MINIMAP_SIZE / TILE_SIZE_MINI;
	helper_minimap(game->map_width, &minmap.end_x, &minmap.start_x);
	helper_minimap(game->map_height, &minmap.end_y, &minmap.start_y);
	if (minmap.start_x < 0)
		minmap.start_x = 0;
	if (minmap.start_y < 0)
		minmap.start_y = 0;
	render_minimap_viewport(game, mlx, minmap);
	draw_player(game, mlx, minmap);
	draw_direction_line(game, mlx, minmap);
}
