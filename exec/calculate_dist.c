/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_dist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 11:21:37 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	compute_ray_properties(t_game *game, t_ray *ray)
{
	double	raydirx;
	double	raydiry;

	if (ray->raydirx == 0)
		raydirx = 1e30;
	else
		raydirx = fabs(1 / ray->raydirx);
	ray->deltadistx = raydirx;
	if (ray->raydiry == 0)
		raydiry = 1e30;
	else
		raydiry = fabs(1 / ray->raydiry);
	ray->deltadisty = raydiry;
	if (ray->raydirx < 0)
		ray->stepx = -1;
	else
		ray->stepx = 1;
	if (ray->raydiry < 0)
		ray->stepy = -1;
	else
		ray->stepy = 1;
}

void	calculate_side_dist(t_game *game, t_ray *ray)
{
	if (ray->raydirx < 0)
		ray->sidedistx = ((game->posx - ray->mapx) * ray->deltadistx);
	else
		ray->sidedistx = ((ray->mapx + 1.0 - game->posx) * ray->deltadistx);
	if (ray->raydiry < 0)
		ray->sidedisty = ((game->posy - ray->mapy) * ray->deltadisty);
	else
		ray->sidedisty = ((ray->mapy + 1.0 - game->posy) * ray->deltadisty);
}

void	calculate_ray_direction(t_game *game, t_ray *ray)
{
	ray->camerax = (2 * game->currentstripe / (double)WIDTH - 1);
	ray->raydirx = game->dirx + game->planex * ray->camerax;
	ray->raydiry = game->diry + game->planey * ray->camerax;
}
