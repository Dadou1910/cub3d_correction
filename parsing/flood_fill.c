/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 12:50:56 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_map_copy(char **map_copy, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		free(map_copy[y]);
		y++;
	}
	free(map_copy);
}

void	check_map_copy(t_game *game, char **map_copy)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == '0')
			{
				free_map_copy(map_copy, game->map_height);
				cleanup_and_exit(game, game->mlx, "Inaccessible areas");
			}
			x++;
		}
		y++;
	}
}

void	validate_accessible_map(t_game *game)
{
	int		y;
	char	**map_copy;

	map_copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_copy)
		check_malloc(game, game->mlx);
	y = 0;
	while (y < game->map_height)
	{
		map_copy[y] = ft_strdup(game->map[y]);
		if (!map_copy[y])
			check_malloc(game, game->mlx);
		y++;
	}
	map_copy[y] = NULL;
	flood_fill(map_copy, (int)game->posx, (int)game->posy, game);
	check_map_copy(game, map_copy);
	free_map_copy(map_copy, game->map_height);
}

void	helper_orient(t_game *game, char orientation)
{
	if (orientation == 'N')
	{
		game->dirx = 0;
		game->diry = -1;
		game->planex = 0.66;
		game->planey = 0;
		game->angle = 3 * M_PI / 2;
	}
	else if (orientation == 'S')
	{
		game->dirx = 0;
		game->diry = 1;
		game->planex = -0.66;
		game->planey = 0;
		game->angle = M_PI / 2;
	}
}

void	set_player_orientation(t_game *game, char orientation)
{
	if (orientation == 'N' || orientation == 'S')
		helper_orient(game, orientation);
	else if (orientation == 'E')
	{
		game->dirx = 1;
		game->diry = 0;
		game->planex = 0;
		game->planey = 0.66;
		game->angle = 0;
	}
	else if (orientation == 'W')
	{
		game->dirx = -1;
		game->diry = 0;
		game->planex = 0;
		game->planey = -0.66;
		game->angle = M_PI;
	}
}
