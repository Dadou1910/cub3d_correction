/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dimension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2025/02/03 15:56:16 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	helper_dimension(t_game *game, int *y, char c)
{
	int	x;

	x = 0;
	while (x < game->map_width)
	{
		if (game->map[*y][x] == ' ')
			game->map[*y][x] = c;
		x++;
	}
}

void	help_dimension(t_game *game, char c)
{
	int		y;
	int		x;
	char	*padded_row;

	y = 0;
	while (y < game->map_height)
	{
		if (strlen(game->map[y]) < game->map_width)
		{
			padded_row = malloc(game->map_width + 1);
			if (!padded_row)
			{
				printf("%s\n", "Error\nMalloc failed");
				clean_exit(game, game->mlx);
			}
			ft_memcpy(padded_row, game->map[y], strlen(game->map[y]));
			ft_memset(padded_row + strlen(game->map[y]), c,
				game->map_width - strlen(game->map[y]));
			padded_row[game->map_width] = '\0';
			free(game->map[y]);
			game->map[y] = padded_row;
		}
		helper_dimension(game, &y, c);
		y++;
	}
}

void	calculate_map_dimensions(t_game *game)
{
	int	y;
	int	max_width;
	int	row_width;

	y = 0;
	max_width = 0;
	row_width = 0;
	while (game->map[y])
	{
		row_width = (int)ft_strlen(game->map[y]);
		if (row_width > max_width)
			max_width = row_width;
		y++;
	}
	game->map_height = y;
	game->map_width = max_width;
}

void	validate_config(t_mlx *mlx)
{
	if (!is_valid_color(mlx->floor_color, "floor"))
		cleanup_and_exit(NULL, mlx, "Invalid floor color");
	if (!is_valid_color(mlx->ceiling_color, "ceiling"))
		cleanup_and_exit(NULL, mlx, "Invalid ceiling color");
}
