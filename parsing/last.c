/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2025/02/02 20:22:56 by dadou            ###   ########.fr       */
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
