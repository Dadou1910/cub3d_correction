/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/31 12:32:04 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_mlx_null(t_mlx *mlx)
{
	mlx->mlx = NULL;
	mlx->mlx_win = NULL;
	mlx->img = NULL;
	mlx->addr = NULL;
	mlx->north_texture.img = NULL;
	mlx->south_texture.img = NULL;
	mlx->east_texture.img = NULL;
	mlx->west_texture.img = NULL;
}

void	init_temp(t_temp temp)
{
	temp.texpos = 0;
	temp.texx = 0;
	temp.texy = 0;
	temp.color = 0;
	temp.step = 0;
	temp.side = 0;
}
