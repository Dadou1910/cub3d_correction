/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2025/02/03 23:00:28 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (!mlx || !mlx->addr)
	{
		printf("%s", "Error\nImage data not initialized\n");
		return ;
	}
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_screen(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(mlx, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	update_player(t_game *game)
{
	move_player(game, MOVE_SPEED);
	if (game->keys.a)
		rotate_player(game, -ROTATION_SPEED);
	if (game->keys.d)
		rotate_player(game, ROTATION_SPEED);
}

int	render_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	update_player(game);
	render_frame(game, &game->ray, game->map, game->mlx);
	render_minimap(game, game->mlx);
	game->init = 1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;
	t_mlx	*mlx;

	if (argc != 2)
	{
		printf("%s", "Error\nInvalid number of arguments\n");
		return (0);
	}
	game = malloc(sizeof(t_game));
	if (!game)
		exit(1);
	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		check_malloc(game, game->mlx);
	init_mlx(game, mlx);
	init_game(game, mlx);
	parse_file(argv[1], game, mlx);
	calculate_map_dimensions(game);
	validate_config(mlx);
	validate_map(game);
	validate_accessible_map(game);
	key_events(game, mlx);
	mlx_loop_hook(mlx->mlx, render_loop, game);
	mlx_loop(mlx->mlx);
	return (0);
}
