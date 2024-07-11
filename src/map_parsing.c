/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:05:12 by jpointil          #+#    #+#             */
/*   Updated: 2024/07/11 15:33:58 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_file_format(char *path, int fd)
{
	int	file_len;

	fd = open(path, __O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		ft_printf(RED "failed to open file\n" RESET);
		exit(1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(RED "failed to open file\n" RESET);
		exit(1);
	}
	file_len = ft_strlen(path);
	if (file_len < 4 || !ft_strnstr(&path[file_len - 4], ".ber", 4))
	{
		ft_printf(RED "MapError : please provide a .ber file\n" RESET);
		exit(1);
	}
	return (fd);
}

void	map_fill(t_map *map, int fd, int readed, char *new_line)
{
	map->big_line = ft_calloc(1, sizeof(char));
	new_line = ft_calloc(BUFFERSIZE + 1, (sizeof(char)));
	if (!new_line || !map->big_line)
		game_error((void *)map, MAP, "please retry");
	while (readed > 0)
	{
		readed = read(fd, new_line, BUFFERSIZE);
		if (readed == -1)
			(free(new_line), free(map->big_line), game_error((void *)map, R,
					""));
		if (readed == 0)
			break ;
		new_line[readed] = '\0';
		map->big_line = ft_strjoin_free(map->big_line, new_line);
		if (!map->big_line)
			game_error((void *)map, MAP, "Malloc error");
	}
	free(new_line);
	close(fd);
	map->tiles = ft_split(map->big_line, '\n');
	check_big_line(map->big_line, map);
	if (!map->tiles)
		game_error((void *)map, MAP, "please retry");
}

void	map_elements(t_map *map, char tile, int x, int y)
{
	if (tile == 'C')
		map->collectibles++;
	if (tile == 'E')
	{
		if (map->exit)
			game_error((void *)map, MAP, "more than one exit");
		map->exit = true;
		map->exit_x = x;
		map->exit_y = y;
	}
	if (tile == 'P')
	{
		if (map->player)
			game_error((void *)map, MAP, "more than one player spawn");
		map->player = true;
		map->player_x = x;
		map->player_y = y;
	}
	return ;
}

void	check_map_is_rect(t_map *map, int x, int y)
{
	map->player = false;
	map->exit = false;
	map->collectibles = 0;
	if (map->height < 3 || map->width < 5)
		game_error((void *)map, MAP, "map is too little");
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if ((y == 0 || y == (map->height - 1)) && map->tiles[y][x] != '1')
				game_error((void *)map, MAP, "map border must be only '1'");
			if (map->tiles[y][x] == 'E' || map->tiles[y][x] == 'P'
				|| map->tiles[y][x] == 'C')
				map_elements(map, map->tiles[y][x], x, y);
			else if (map->tiles[y][x] != '1' && map->tiles[y][x] != '0')
				game_error((void *)map, MAP,
					"map must be only composed of '01PEC'");
		}
		if (map->tiles[y][0] != '1' || map->tiles[y][map->width - 1] != '1')
			game_error((void *)map, MAP, "map border must be only '1'");
	}
	if (map->collectibles == 0 || !map->player || !map->exit)
		game_error((void *)map, MAP, "collectible, player, and exit needed");
}

t_map	*map_init(char *path)
{
	int		fd;
	t_map	*map;

	fd = 0;
	fd = check_file_format(path, fd);
	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
		(close(fd), game_error((void *)map, MAP, "please retry"));
	map_fill(map, fd, 1, NULL);
	if (map->tiles[0] == NULL)
		game_error((void *)map, MAP, "please retry");
	close(fd);
	map->width = ft_strlen(map->tiles[0]);
	map->height = 0;
	while (map->tiles[map->height])
		map->height++;
	check_map_is_rect(map, -1, -1);
	map->accessible_exit = false;
	map->collected = 0;
	check_map_is_playable(map);
	return (map);
}
