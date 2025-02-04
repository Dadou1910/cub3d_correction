/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2025/02/03 22:58:43 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map[i])
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
	}
	free(map);
}

void	destroy_mlx(t_mlx *mlx)
{
	if (mlx->north_texture.img)
		mlx_destroy_image(mlx->mlx, mlx->north_texture.img);
	if (mlx->south_texture.img)
		mlx_destroy_image(mlx->mlx, mlx->south_texture.img);
	if (mlx->east_texture.img)
		mlx_destroy_image(mlx->mlx, mlx->east_texture.img);
	if (mlx->west_texture.img)
		mlx_destroy_image(mlx->mlx, mlx->west_texture.img);
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->mlx_win)
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	free(mlx);
}

void	cleanup_and_exit(t_game *game, t_mlx *mlx, const char *error_msg)
{
	if (error_msg)
		printf("Error\n%s\n", error_msg);
	if (game->buffer)
		free(game->buffer);
	if (game && game->map)
		free(game->map);
	if (game)
		free(game);
	if (mlx)
		destroy_mlx(mlx);
	exit(1);
}

void	clean_exit(t_game *game, t_mlx *mlx)
{
	if (game && game->map)
		free_map(game->map);
	if (game->buffer)
		free(game->buffer);
	if (game)
		free(game);
	destroy_mlx(mlx);
	exit(1);
}

int	is_surrounded_by_walls(t_game *game)
{
	int		y;
	int		x;

	y = 0;
	helper_surrounded(game, x, y);
	while (y < game->map_height)
	{
		x = 0;
		while (x < (int)strlen(game->temp_map[y]))
		{
			if (game->temp_map[y][x] == '0')
			{
				flood_fill2(game->temp_map, x, y, game);
				break ;
			}
			x++;
		}
		if (game->touches_border)
			break ;
		y++;
	}
	y = 0;
	free_map(game->temp_map);
	return (game->touches_border);
}
