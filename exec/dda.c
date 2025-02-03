/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 10:56:52 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	helper_ddax(t_game *game)
{
	game->ray.sidedistx += game->ray.deltadistx;
	game->ray.mapx += game->ray.stepx;
	return (0);
}

int	helper_dday(t_game *game)
{
	game->ray.sidedisty += game->ray.deltadisty;
	game->ray.mapy += game->ray.stepy;
	return (1);
}

void	perform_dda(t_game *game, char **map, int *hit, int *side)
{
	*hit = 0;
	while (*hit == 0)
	{
		if (game->ray.mapx < 0 || game->ray.mapx >= game->map_width
			|| game->ray.mapy < 0 || game->ray.mapy >= game->map_height
			|| !map[game->ray.mapy][game->ray.mapx])
			cleanup_and_exit(game, game->mlx, "Ray out of bound");
		if (game->ray.sidedistx < game->ray.sidedisty)
			*side = helper_ddax(game);
		else
			*side = helper_dday(game);
		if (game->ray.mapx < 0 || game->ray.mapx >= game->map_width
			|| game->ray.mapy < 0 || game->ray.mapy >= game->map_height
			|| !map[game->ray.mapy][game->ray.mapx])
			cleanup_and_exit(game, game->mlx, "Ray out of bound");
		if (map[game->ray.mapy][game->ray.mapx] == '1')
			*hit = 1;
	}
}

void	help_raycasting(t_game *game, t_ray *ray, double *perp_wall_dist,
			int side)
{
	if (side == 0)
		*perp_wall_dist = (ray->mapx - game->posx
				+ (1 - ray->stepx) / 2) / ray->raydirx;
	else
		*perp_wall_dist = (ray->mapy - game->posy
				+ (1 - ray->stepy) / 2) / ray->raydiry;
	if (*perp_wall_dist < 0.01)
		*perp_wall_dist = 0.01;
}

void	process_raycasting(t_game *game, t_ray *ray, t_mlx *mlx)
{
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	double	wallx;

	hit = 0;
	calculate_ray_direction(game, ray);
	compute_ray_properties(game, ray);
	calculate_side_dist(game, ray);
	perform_dda(game, game->map, &hit, &side);
	help_raycasting(game, ray, &perp_wall_dist, side);
	line_height = (int)(HEIGHT / perp_wall_dist);
	game->drawstart = -line_height / 2 + HEIGHT / 2;
	game->drawend = line_height / 2 + HEIGHT / 2;
	if (side == 0)
		wallx = game->posy + perp_wall_dist * ray->raydiry;
	else
		wallx = game->posx + perp_wall_dist * ray->raydirx;
	wallx -= (int)wallx;
	render_textured_column(game, game->currentstripe, side, wallx);
}
