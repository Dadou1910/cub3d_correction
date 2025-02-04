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

int is_valid_cub_file(const char *filename)
{
    int len;

    if (!filename)
        return (0);
    len = ft_strlen(filename);
    if (len < 4)
        return (0);
    if (ft_strcmp((char *)(filename + len - 4), ".cub") == 0)
        return (1);
    return (0);
}

int	check_row_sides(char **map, int height)
{
	int	y;
	int	row_length;

	y = 0;
	while (y < height)
	{
		row_length = ft_strlen(map[y]);
		if (row_length == 0)
			return (1);
		if (map[y][0] != '1' || map[y][row_length - 1] != '1')
			return (1);
		y++;
	}
	return (0);
}

int	check_top_bottom(char **map, int height)
{
	int	x;
	int	width;

	width = ft_strlen(map[0]);
	x = 0;
	while (x < width)
	{
		if (map[0][x] != '1' || map[height - 1][x] != '1')
			return (1);
		x++;
	}
	return (0);
}
