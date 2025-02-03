/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 11:38:57 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	render_ceiling(t_mlx *mlx, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(mlx, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_floor(t_mlx *mlx, int color)
{
	int	x;
	int	y;

	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(mlx, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_textured_column(t_game *game, int x,
			t_texture *texture, t_temp temp)
{
	int	y;

	temp.step = 1.0 * texture->height / (game->drawend - game->drawstart);
	if (game->drawstart < 0)
		temp.texpos = -game->drawstart * temp.step;
	else
		temp.texpos = 0.0;
	if (game->drawend >= HEIGHT)
		game->drawend = HEIGHT - 1;
	if (game->drawstart < 0)
		y = 0;
	else
		y = game->drawstart;
	while (y < game->drawend)
	{
		temp.texy = (int)temp.texpos & (texture->height - 1);
		temp.texpos += temp.step;
		temp.color = *(unsigned int *)(texture->addr
				+ (temp.texy * texture->line_len
					+ temp.texx * (texture->bpp / 8)));
		if (temp.side == 1)
			temp.color = (temp.color >> 1) & 0x7F7F7F;
		my_mlx_pixel_put(game->mlx, x, y, temp.color);
		y++;
	}
}

void	render_textured_column(t_game *game, int x, int side, double wallx)
{
	t_texture	*texture;
	t_temp		temp;

	init_temp(temp);
	temp.side = side;
	texture = select_texture(game, game->mlx, side);
	temp.texx = (int)(wallx * (double)texture->width);
	if ((side == 0 && game->ray.raydirx > 0)
		|| (side == 1 && game->ray.raydiry < 0))
		temp.texx = texture->width - temp.texx - 1;
	draw_textured_column(game, x, texture, temp);
}

void	render_frame(t_game *game, t_ray *ray, char **map, t_mlx *mlx)
{
	int	stripe;

	stripe = 0;
	clear_screen(mlx);
	render_ceiling(mlx, mlx->ceiling_color);
	render_floor(mlx, mlx->floor_color);
	while (stripe < WIDTH)
	{
		game->currentstripe = stripe;
		ray->mapx = (int)game->posx;
		ray->mapy = (int)game->posy;
		process_raycasting(game, ray, mlx);
		stripe++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
}
