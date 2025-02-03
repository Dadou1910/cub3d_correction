/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 13:20:44 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_ray(t_ray ray)
{
	ray.raydirx = 0.0;
	ray.raydiry = 0.0;
	ray.deltadistx = 0.0;
	ray.deltadisty = 0.0;
	ray.sidedistx = 0.0;
	ray.sidedisty = 0.0;
	ray.camerax = 0.0;
	ray.stepx = 0;
	ray.stepy = 0;
	ray.mapx = 0;
	ray.mapy = 0;
}

void	init_count(t_game *game)
{
	game->count[0] = 0;
	game->count[1] = 0;
	game->count[2] = 0;
	game->count[3] = 0;
	game->count[4] = 0;
	game->count[5] = 0;
}

void	init_minmap(t_game *game)
{
	game->minmap.start_x = 0;
	game->minmap.start_y = 0;
	game->minmap.end_x = 0;
	game->minmap.end_y = 0;
}

void	init_game(t_game *game, t_mlx *mlx)
{
	game->angle = 0.0;
	game->posx = 0;
	game->posy = 0;
	game->dirx = 0;
	game->diry = 0;
	game->planex = 0;
	game->planey = 0;
	game->map = NULL;
	game->currentstripe = 0;
	init_ray(game->ray);
	game->map_width = 0;
	game->map_height = 0;
	init_count(game);
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.w = 0;
	game->keys.d = 0;
	game->init = 0;
	game->mlx = mlx;
	game->map_started = 0;
	game->drawend = 0;
	game->drawstart = 0;
	game->buffer = NULL;
}

void	init_mlx(t_mlx *mlx)
{
	init_mlx_null(mlx);
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
}
