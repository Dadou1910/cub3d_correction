/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dimension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/31 12:13:46 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	help_dimension(t_game *game, int *row_len, int *y)
{
	char	*padded_row;

	if (*row_len < game->map_width)
	{
		padded_row = malloc(game->map_width + 1);
		if (!padded_row)
			check_malloc(game, game->mlx);
		ft_memcpy(padded_row, game->map[*y], *row_len);
		ft_memset(padded_row + *row_len, ' ', game->map_width - *row_len);
		padded_row[game->map_width] = '\0';
		free(game->map[*y]);
		game->map[*y] = padded_row;
	}
}

void	calculate_map_dimensions(t_game *game)
{
	int	y;
	int	row_len;
	int	max_width;
	int	row_width;

	if (!game->map)
		cleanup_and_exit(game, game->mlx, "Invalid file\n");
	y = 0;
	max_width = 0;
	while (game->map[y])
	{
		row_width = ft_strlen(game->map[y]);
		if (row_width > max_width)
			max_width = row_width;
		y++;
	}
	game->map_height = y;
	game->map_width = max_width;
	y = 0;
	while (y < game->map_height)
	{
		row_len = ft_strlen(game->map[y]);
		help_dimension(game, &row_len, &y);
		y++;
	}
}
