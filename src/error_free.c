/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:26:40 by jpointil          #+#    #+#             */
/*   Updated: 2024/07/09 17:53:10 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_map(char **map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		ft_printf(GREEN "%s\n" RESET, map[y]);
		y++;
	}
}

void	free_sprites(t_game *game)
{
	if (game->sprites->player)
		mlx_destroy_image(game->mlx, game->sprites->player);
	if (game->sprites->wall)
		mlx_destroy_image(game->mlx, game->sprites->wall);
	if (game->sprites->floor)
		mlx_destroy_image(game->mlx, game->sprites->floor);
	if (game->sprites->collectibles)
		mlx_destroy_image(game->mlx, game->sprites->collectibles);
	if (game->sprites->exit)
		mlx_destroy_image(game->mlx, game->sprites->exit);
	free(game->sprites);
}

void	free_map(t_map *map)
{
	int	y;

	if (map)
	{
		if (map->tiles)
		{
			y = 0;
			while (map->tiles[y] != NULL)
			{
				free(map->tiles[y]);
				y++;
			}
			free(map->tiles);
		}
		if (map->big_line)
			free(map->big_line);
	}
	free(map);
}

void	free_game(t_game *game)
{
	if (game)
	{
		if (game->sprites)
			free_sprites(game);
		if (game->mlx_win)
			mlx_destroy_window(game->mlx, game->mlx_win);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
		if (game->map)
			free_map(game->map);
	}
	exit(0);
}

void	game_error(void *ptr, t_type type, char *message)
{
	if (type == GAME)
	{
		ft_printf(RED "GameError :\n%s\n" RESET, message);
		free_game(ptr);
	}
	if (type == MAP)
	{
		ft_printf(RED "MapError :\n%s\n" RESET, message);
		free_map(ptr);
	}
	if (type == SPRITE)
	{
		ft_printf(RED "RenderError :\n%s\n" RESET, message);
		free_game(ptr);
	}
	if (type == R)
		ft_printf(RED "MapError : \n%s\n" RESET, message);
	exit(-1);
}
