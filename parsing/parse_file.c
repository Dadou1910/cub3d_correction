/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2025/02/02 20:18:57 by dadou            ###   ########.fr       */
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
			printf("Error\nInvalid character '%c' in map \n", line[x]);
			clean_exit(game, game->mlx);
		}
		x++;
	}
}

int	map_not_started(char *line, t_game *game, char **map)
{
	char	*test_line;

	test_line = trim_whitespace(line);
	if (line[0] == '\0' || line[0] == '\n')
		return (0);

	// If map has started, do NOT accept texture/colors after it
	if (game->map_started)
	{
		if (!check_text(test_line))
		{
			free(line);
			free_map(map);
			cleanup_and_exit(game, game->mlx, "Error\nTexture/color found after map start\n");
		}
	}
	
	if (!check_text(test_line))
		parse_config(test_line, line, game, map);
	else if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
	{
		game->map_started = 1;  // Flag that the map has begun
		return (1);
	}
	else
	{
		printf("Error\nInvalid line -> %s", line);
		free(line);
		free_map(map);
		clean_exit(game, game->mlx);
	}
	return (0);
}


// int	map_not_started(char *line, t_game *game, char **map)
// {
// 	char	*test_line;

// 	test_line = trim_whitespace(line);
// 	if (line[0] == '\0' || line[0] == '\n')
// 		return (0);
// 	if (!check_text(test_line))
// 		parse_config(test_line, line, game, map);
// 	else if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
// 		return (1);
// 	else
// 	{
// 		printf("Errorn\nInvalid line -> %s", line);
// 		free(line);
// 		free_map(map);
// 		clean_exit(game, game->mlx);
// 	}
// 	return (0);
// }

// char	*map_has_started(t_game *game, char *line, char **map, int ms)
// {
// 	int	len;
// 	if (!ms)
// 	{
// 		if (check_duplicate_or_missing(game, game->mlx))
// 		{
// 			free(line);
// 			free_map(map);
// 			cleanup_and_exit(game, game->mlx, "Duplicate or missing texture");
// 		}
// 	}
// 	len = ft_strlen(line);
// 	if (len > 0 && line[len - 1] == '\n')
// 		line[len - 1] = '\0';
// 	check_map_char(line, game);
// 	return (line);
// }

char	*map_has_started(t_game *game, char *line, char **map, int ms)
{
	int	len;

	if (!ms)
	{
		if (check_duplicate_or_missing(game, game->mlx))
		{
			free(line);
			free_map(map);
			cleanup_and_exit(game, game->mlx, "Duplicate or missing texture");
		}
	}

	// Reject floor/ceiling colors inside the map
	if (strncmp(line, "F ", 2) == 0 || strncmp(line, "C ", 2) == 0)
	{
		free(line);
		free_map(map);
		cleanup_and_exit(game, game->mlx, "Error\nFloor/Ceiling colors found inside the map\n");
	}

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	check_map_char(line, game);
	return (line);
}


void	helper_parse_file(t_game *game, char *line, int *y, char **map)
{
	int	map_started;

	map_started = 0;
	if (!map_started)
		map_started = map_not_started(line, game, map);
	if (map_started)
	{
		if (*y >= 4096)
		{
			free(line);
			free_map(map);
			cleanup_and_exit(game, game->mlx, "Map too big\n");
		}
		map[*y] = ft_strdup(map_has_started(game, line, map, map_started));
		(*y)++;
		map[*y] = NULL;
	}
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

void	parse_file(const char *filename, t_game *game, t_mlx *mlx)
{
	int		y;
	int		fd;
	char	*line;
	char	**map;

	if (!is_valid_cub_file(filename))
		cleanup_and_exit(game, mlx, "Invalid file format (not .cub)");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		cleanup_and_exit(game, mlx, "Couldn't open map file");
	y = 0;
	map = malloc(sizeof(char *) * 4096);
	if (!map)
		check_malloc(game, mlx);
	line = get_next_line(fd, game);
	while (line)
	{
		helper_parse_file(game, line, &y, map);
		free(line);
		line = get_next_line(fd, game);
	}
	free(line);
	map[y] = NULL;
	game->map = map;
	close(fd);
}


// void	parse_file(const char *filename, t_game *game, t_mlx *mlx)
// {
// 	int		y;
// 	int		fd;
// 	char	*line;
// 	char	**map;

// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		cleanup_and_exit(game, mlx, "Couldn't open map file");
// 	y = 0;
// 	map = malloc(sizeof(char *) * 4096);
// 	if (!map)
// 		check_malloc(game, mlx);
// 	line = get_next_line(fd, game);
// 	while (line)
// 	{
// 		helper_parse_file(game, line, &y, map);
// 		free(line);
// 		line = get_next_line(fd, game);
// 	}
// 	free(line);
// 	map[y] = NULL;
// 	game->map = map;
// 	close(fd);
// }
