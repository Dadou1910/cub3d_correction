/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/31 14:54:59 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	help_walls_count(t_game *game, int x, int y, int *count)
{
	if (game->map[y][x] == '1' && (y == 0 || x == 0
		|| y == game->map_height - 1 || x == game->map_width - 1))
	{
		if (y > 0 && game->map[y - 1][x] == '1')
			(*count)++;
		if (y < game->map_height - 1 && game->map[y + 1][x] == '1')
			(*count)++;
		if (x > 0 && game->map[y][x - 1] == '1')
			(*count)++;
		if (x < game->map_width - 1 && game->map[y][x + 1] == '1')
			(*count)++;
		if (y > 0 && x > 0 && game->map[y - 1][x - 1] == '1')
			(*count)++;
		if (y > 0 && x < game->map_width - 1 && game->map[y - 1][x + 1] == '1')
			(*count)++;
		if (y < game->map_height - 1 && x > 0 && game->map[y + 1][x - 1] == '1')
			(*count)++;
		if (y < game->map_height - 1 && x < game->map_width - 1
			&& game->map[y + 1][x + 1] == '1')
			(*count)++;
		return (*count >= 2);
	}
	return (1);
}

int	is_surrounded_by_walls(t_game *game)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (!help_walls(game, x, y))
				return (0);
			if (!help_walls_count(game, x, y, &count))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	helper_val_map(t_game *game, int *player_count, int x, int y)
{
	(*player_count)++;
	game->posx = x + 0.5;
	game->posy = y + 0.5;
	set_player_orientation(game, game->map[y][x]);
	game->map[y][x] = '0';
}

void	check_val_map(t_game *game, int player_count)
{
	if (player_count != 1)
	{
		if (player_count == 0)
			cleanup_and_exit(game, game->mlx, "No player position");
		else
			cleanup_and_exit(game, game->mlx, "Multiple player positions");
	}
	if (!is_surrounded_by_walls(game))
		cleanup_and_exit(game, game->mlx,
			"Map is not properly surrounded by walls");
}

void	validate_map(t_game *game)
{
	int	y;
	int	x;
	int	player_count;

	x = 0;
	y = 0;
	player_count = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (!is_valid_map_char(game->map[y][x]))
				cleanup_and_exit(game, game->mlx, "Invalid map char");
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
				helper_val_map(game, &player_count, x, y);
			x++;
		}
		y++;
	}
	check_val_map(game, player_count);
}
