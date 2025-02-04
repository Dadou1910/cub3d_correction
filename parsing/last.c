/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2025/02/03 23:07:04 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return ;
	if (x >= (int)strlen(map[y]))
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

int	check_text(char *line)
{
	if ((strncmp(line, "NO ", 3) == 0)
		|| (strncmp(line, "SO ", 3) == 0)
		|| (strncmp(line, "WE ", 3) == 0)
		|| (strncmp(line, "EA ", 3) == 0)
		|| (strncmp(line, "F ", 2) == 0)
		|| (strncmp(line, "C ", 2) == 0))
		return (0);
	else
		return (1);
}

int	is_valid_cub_file(const char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strcmp((char *)(filename + len - 4), ".cub") == 0)
		return (1);
	return (0);
}

void	flood_fill2(char **map, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
	{
		game->touches_border = 1;
		return ;
	}
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	map[y][x] = 'X';
	flood_fill2(map, x + 1, y, game);
	flood_fill2(map, x - 1, y, game);
	flood_fill2(map, x, y + 1, game);
	flood_fill2(map, x, y - 1, game);
}

void	helper_surrounded(t_game *game, int x, int y)
{
	game->temp_map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->temp_map)
	{
		printf("%s", "Error\nMalloc failed\n");
		clean_exit(game, game->mlx);
	}
	y = 0;
	while (y < game->map_height)
	{
		game->temp_map[y] = strdup(game->map[y]);
		if (!game->temp_map[y])
		{
			free(game->temp_map);
			printf("%s", "Error\nMalloc failed\n");
			clean_exit(game, game->mlx);
		}
		y++;
	}
	game->temp_map[y] = NULL;
}
