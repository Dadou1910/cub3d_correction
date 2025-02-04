/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2025/02/03 23:03:18 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	check_map_char(char *line, t_game *game)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] != '0' && line[x] != '1' && line[x] != ' '
			&& line[x] != 'N' && line[x] != 'S' && line[x] != 'E'
			&& line[x] != 'W')
		{
			free(line);
			printf("%s", "Error\nInvalid character in map\n");
			clean_exit(game, game->mlx);
		}
		x++;
	}
}

int	map_not_started(char *line, t_game *game)
{
	char	*test_line;

	test_line = trim_whitespace(line);
	if (line[0] == '\0' || line[0] == '\n')
		return (0);
	if (!check_text(test_line) && !game->map_started)
		parse_config(test_line, line, game);
	else if (test_line[0] == '1' || test_line[0] == '0')
		return (1);
	else
	{
		if (game->map_started)
		{
			printf("Errorn\nInvalid line -> %s\n", line);
			free(line);
			clean_exit(game, game->mlx);
		}
		else
		{
			free(line);
			cleanup_and_exit(game, game->mlx, "Invalid line in file");
		}
	}
	return (0);
}

char	*map_has_started(t_game *game, char *line)
{
	int	len;

	if (!game->map_started)
	{
		if (check_duplicate_or_missing(game, game->mlx))
		{
			free(line);
			cleanup_and_exit(game, game->mlx, "Duplicate or missing texture");
		}
	}
	if (game->map_started && (ft_strchr(line, 'F') != NULL
			|| ft_strchr(line, 'C') != NULL))
	{
		free(line);
		printf("%s", "Error\nInvalid character in map\n");
		clean_exit(game, game->mlx);
	}
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	check_map_char(line, game);
	return (line);
}

void	helper_parse_file(t_game *game, char *line, int *y)
{
	int	map_started;

	if (!game->map_started)
		game->map_started = map_not_started(line, game);
	if (game->map_started)
	{
		if (*y >= 4096)
		{
			free(line);
			cleanup_and_exit(game, game->mlx, "Map too big\n");
		}
		game->map[*y] = ft_strdup(map_has_started(game, line));
		(*y)++;
		game->map[*y] = NULL;
	}
}

void	parse_file(const char *filename, t_game *game, t_mlx *mlx)
{
	int		y;
	int		fd;
	char	*line;

	if (!is_valid_cub_file(filename))
		cleanup_and_exit(game, mlx, "Invalid file format (not .cub)");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		cleanup_and_exit(game, mlx, "Couldn't open map file");
	y = 0;
	game->map = malloc(sizeof(char *) * 4096);
	if (!game->map)
		check_malloc(game, mlx);
	line = get_next_line(fd, game);
	while (line)
	{
		helper_parse_file(game, line, &y);
		free(line);
		line = get_next_line(fd, game);
	}
	free(line);
	game->map[y] = NULL;
	close(fd);
}
