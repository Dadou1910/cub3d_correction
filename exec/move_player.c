/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/31 15:03:21 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


#include <math.h>

void	rotate_player(t_game *game, double rotationspeed)
{
	double	old_dirx;
	double	old_planex;

	game->angle += rotationspeed;
	if (game->angle < 0)
		game->angle += 2 * M_PI;
	else if (game->angle >= 2 * M_PI)
		game->angle -= 2 * M_PI;
	
	old_dirx = game->dirx;
	game->dirx = cos(game->angle);
	game->diry = sin(game->angle);
	old_planex = game->planex;
	game->planex = -sin(game->angle) * FOV;
	game->planey = cos(game->angle) * FOV;
}

void	help_move(t_game *game, double movespeed, double *x, double *y)
{
	*x = game->posx + game->dirx * movespeed;
	*y = game->posy + game->diry * movespeed;

	if (*x > 0 && *x < game->map_width
		&& *y > 0 && *y < game->map_height
		&& game->map[(int)*y][(int)*x] == '0')
	{
		game->posx = *x;
		game->posy = *y;
	}
}

void	move_player(t_game *game, double movespeed)
{
	double	nextx;
	double	nexty;

	nextx = 0;
	nexty = 0;
	if (game->keys.w)
		help_move(game, movespeed, &nextx, &nexty);
	if (game->keys.s)
	{
		nextx = game->posx - game->dirx * movespeed;
		nexty = game->posy - game->diry * movespeed;
		if (nextx > 0 && nextx < game->map_width
			&& nexty > 0 && nexty < game->map_height
			&& game->map[(int)nexty][(int)nextx] == '0')
		{
			game->posx = nextx;
			game->posy = nexty;
		}
	}
}

