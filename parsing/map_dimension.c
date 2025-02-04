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

void	help_dimension(t_game *game)
{
    int y;
    int x;
    char *padded_row;
	
	y = 0;
    while (y < game->map_height)
    {
        int row_len = strlen(game->map[y]);
        if (row_len < game->map_width)
        {
            padded_row = malloc(game->map_width + 1);
            if (!padded_row)
            {
                printf("%s\n", "Error\nMalloc failed");
                clean_exit(game, game->mlx);
            }
            ft_memcpy(padded_row, game->map[y], row_len);
            ft_memset(padded_row + row_len, '1', game->map_width - row_len); // Fill missing spaces with '1'
            padded_row[game->map_width] = '\0';
            free(game->map[y]);
            game->map[y] = padded_row;
        }
        x = 0;
        while (x < game->map_width)
        {
            if (game->map[y][x] == ' ')
                game->map[y][x] = '1';
            x++;
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
