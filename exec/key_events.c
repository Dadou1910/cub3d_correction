/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 13:18:09 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	clean_exit(game, game->mlx);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		close_window(game);
	if (keycode == LEFT_ARROW || keycode == A_KEY)
		game->keys.a = 1;
	if (keycode == RIGHT_ARROW || keycode == D_KEY)
		game->keys.d = 1;
	if (keycode == W_KEY || keycode == UP_ARROW)
		game->keys.w = 1;
	if (keycode == S_KEY || keycode == DOWN_ARROW)
		game->keys.s = 1;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == W_KEY || key == UP_ARROW)
		game->keys.w = 0;
	if (key == S_KEY || key == DOWN_ARROW)
		game->keys.s = 0;
	if (key == A_KEY || key == LEFT_ARROW)
		game->keys.a = 0;
	if (key == D_KEY || key == RIGHT_ARROW)
		game->keys.d = 0;
	return (0);
}

void	key_events(t_game *game, t_mlx *mlx)
{
	mlx_hook(mlx->mlx_win, 2, 1L << 0, key_press, game);
	mlx_hook(mlx->mlx_win, 3, 1L << 1, key_release, game);
	mlx_hook(mlx->mlx_win, 17, 0, close_window, game);
}
