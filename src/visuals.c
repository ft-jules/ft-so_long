/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:07:45 by jpointil          #+#    #+#             */
/*   Updated: 2024/07/01 18:05:30 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	sprites_init(t_game *game)
{
	game->sprites = ft_calloc(1, sizeof(t_sprites));
	game->sprites->wall = mlx_xpm_file_to_image(game->mlx, "sprites/wall.xpm",
			&game->size, &game->size);
	if (game->sprites->wall == NULL)
		game_error(game, GAME, "failed to open : wall.xpm");
	game->sprites->floor = mlx_xpm_file_to_image(game->mlx, "sprites/floor.xpm",
			&game->size, &game->size);
	if (game->sprites->floor == NULL)
		game_error(game, GAME, "failed to open : floor.xpm");
	game->sprites->player = mlx_xpm_file_to_image(game->mlx,
			"sprites/player.xpm", &game->size, &game->size);
	if (game->sprites->player == NULL)
		game_error(game, GAME, "failed to open : player.xpm");
	game->sprites->exit = mlx_xpm_file_to_image(game->mlx, "sprites/exit.xpm",
			&game->size, &game->size);
	if (game->sprites->exit == NULL)
		game_error(game, GAME, "failed to open : exit.xpm");
	game->sprites->collectibles = mlx_xpm_file_to_image(game->mlx,
			"sprites/collectible.xpm", &game->size, &game->size);
	if (game->sprites->collectibles == NULL)
		game_error(game, GAME, "failed to open : collectible.xpm");
}

void	render_map(t_game *game, int x, int y)
{
	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (++x < game->map->width)
		{
			if (game->map->tiles[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->sprites->wall, x * 32, y * 32);
			if (game->map->tiles[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->sprites->floor, x * 32, y * 32);
			if (game->map->tiles[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->sprites->player, x * 32, y * 32);
			if (game->map->tiles[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->sprites->collectibles, x * 32, y * 32);
			if (game->map->tiles[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->sprites->exit, x * 32, y * 32);
		}
	}
}
