/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_playable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:40:14 by jpointil          #+#    #+#             */
/*   Updated: 2024/07/09 15:35:44 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	cpy_error(t_map *map, char **cpy)
{
	int	i;

	i = -1;
	while (cpy[++i])
		free(cpy[i]);
	game_error(map, MAP, "please retry");
}

char	**create_map_copy(t_map *map)
{
	char	**cpy;
	int		i;

	cpy = malloc(sizeof(char *) * (map->height + 1));
	if (!cpy)
		(free(cpy), game_error(map, MAP, "please retry"));
	i = -1;
	while (++i < map->height)
	{
		cpy[i] = ft_strdup(map->tiles[i]);
		if (!cpy[i])
			cpy_error(map, cpy);
	}
	cpy[i] = NULL;
	return (cpy);
}

void	pathfinder(t_map *map, char **mapcpy, int x, int y)
{
	if (mapcpy[y][x] == '1' || mapcpy[y][x] == VISITED_TILE
		|| mapcpy[y][x] == COLLECTED_COLLECTIBLE
		|| mapcpy[y][x] == VISITED_SPAWN)
		return ;
	if (mapcpy[y][x] == 'P')
		mapcpy[y][x] = VISITED_SPAWN;
	if (mapcpy[y][x] == '0')
		mapcpy[y][x] = VISITED_TILE;
	if (mapcpy[y][x] == 'C')
	{
		map->collected++;
		mapcpy[y][x] = COLLECTED_COLLECTIBLE;
	}
	if (mapcpy[y][x] == 'E')
	{
		map->accessible_exit = true;
		return ;
	}
	pathfinder(map, mapcpy, x + 1, y);
	pathfinder(map, mapcpy, x - 1, y);
	pathfinder(map, mapcpy, x, y + 1);
	pathfinder(map, mapcpy, x, y - 1);
}

void	check_map_is_playable(t_map *map)
{
	char	**cpy;
	int		i;

	cpy = create_map_copy(map);
	if (!cpy)
		cpy_error(map, cpy);
	pathfinder(map, cpy, map->player_x, map->player_y);
	i = -1;
	while (cpy[++i])
		free(cpy[i]);
	free(cpy);
	if (map->collected != map->collectibles || !map->accessible_exit)
		game_error(map, MAP, "map is not playable");
	map->collected = 0;
}
