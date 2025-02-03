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

void	help_dimension(t_game *game)
{
    int y;
	
	y = 0;
    while (y < game->map_height)
    {
        int row_len = strlen(game->map[y]);
        if (row_len < game->map_width)
        {
            char *padded_row = malloc(game->map_width + 1);
            if (!padded_row)
                cleanup_and_exit(game, game->mlx, "Malloc failed");
            ft_memcpy(padded_row, game->map[y], row_len);
            ft_memset(padded_row + row_len, ' ', game->map_width - row_len);
            padded_row[game->map_width] = '\0';
            free(game->map[y]);
            game->map[y] = padded_row;
        }
        y++;
	}
}

void	calculate_map_dimensions(t_game *game)
{
    int y = 0;
    int max_width = 0;
	int row_width = 0;

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
