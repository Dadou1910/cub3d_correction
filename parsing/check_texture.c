/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2025/02/03 16:04:31 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_duplicate_or_missing(t_game *game, t_mlx *mlx)
{
	if (game->count[0] > 1 || game->count[0] == 0)
		return (1);
	if (game->count[1] > 1 || game->count[1] == 0)
		return (1);
	if (game->count[2] > 1 || game->count[2] == 0)
		return (1);
	if (game->count[3] > 1 || game->count[3] == 0)
		return (1);
	if (game->count[4] > 1 || game->count[4] == 0)
		return (1);
	if (game->count[5] > 1 || game->count[5] == 0)
		return (1);
	return (0);
}

void	validate_config_map(char *line, t_game *game, t_mlx *mlx)
{
	if (strncmp(line, "NO ", 3) == 0)
		game->count[0]++;
	else if (strncmp(line, "SO ", 3) == 0)
		game->count[1]++;
	else if (strncmp(line, "WE ", 3) == 0)
		game->count[2]++;
	else if (strncmp(line, "EA ", 3) == 0)
		game->count[3]++;
	else if (strncmp(line, "F ", 2) == 0)
		game->count[4]++;
	else if (strncmp(line, "C ", 2) == 0)
		game->count[5]++;
}

int	is_valid_xpm_file(char *filename)
{
	int		len;
	int		fd;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".xpm", 4) != 0)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	parse_config(char *line, char *li, t_game *game)
{
	char	*trimmed;

	trimmed = trim_whitespace(line);
	validate_config_map(trimmed, game, game->mlx);
	if (ft_strncmp(trimmed, "NO ", 3) == 0 && is_valid_xpm_file(trimmed + 3)
		&& !game->mlx->north_texture.img)
		load_texture(game->mlx, &game->mlx->north_texture, game, trimmed + 3);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0
		&& is_valid_xpm_file(trimmed + 3) && !game->mlx->south_texture.img)
		load_texture(game->mlx, &game->mlx->south_texture, game, trimmed + 3);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0
		&& is_valid_xpm_file(trimmed + 3) && !game->mlx->west_texture.img)
		load_texture(game->mlx, &game->mlx->west_texture, game, trimmed + 3);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0
		&& is_valid_xpm_file(trimmed + 3) && !game->mlx->east_texture.img)
		load_texture(game->mlx, &game->mlx->east_texture, game, trimmed + 3);
	else if (!ft_strncmp(trimmed, "F ", 2) && !game->mlx->floor_color)
		game->mlx->floor_color = parse_color(game, trimmed + 2, li);
	else if (!ft_strncmp(trimmed, "C ", 2) && !game->mlx->ceiling_color)
		game->mlx->ceiling_color = parse_color(game, trimmed + 2, li);
	else
	{
		free(li);
		cleanup_and_exit(game, game->mlx, "Invalid map configuration");
	}
}

int	is_valid_color(int color, const char *type)
{
	if (!color)
		return (1);
	if (color < 0x000000 || color > 0xFFFFFF)
		return (0);
	return (1);
}
