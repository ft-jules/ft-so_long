/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 23:12:32 by jules             #+#    #+#             */
/*   Updated: 2024/07/09 14:28:05 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	player_movements(t_game *game, int n_x, int n_y)
{
	if (n_x == game->map->exit_x && n_y == game->map->exit_y)
	{
		if (game->map->collected == game->map->collectibles)
		{
			ft_printf(YELLOW "WP YOU ESCAPED THE DUNGEON !!\n" RESET);
			free_game(game);
		}
		else
			game->map->tiles[n_y][n_x] = '0';
	}
	else if (game->map->tiles[n_y][n_x] == '1')
		return ;
	else if (game->map->tiles[n_y][n_x] == 'C')
	{
		game->map->collected++;
		game->map->tiles[n_y][n_x] = '0';
	}
	game->map->tiles[game->map->player_y][game->map->player_x] = '0';
	game->map->player_x = n_x;
	game->map->player_y = n_y;
	game->map->tiles[game->map->exit_y][game->map->exit_x] = 'E';
	game->map->tiles[game->map->player_y][game->map->player_x] = 'P';
	game->steps++;
	ft_printf(MAGENTA "Steps: %d\n" RESET, game->steps);
	render_map(game, 0, 0);
}

int	key_handler(int key, t_game *game)
{
	if (key == KEY_W)
		player_movements(game, game->map->player_x, game->map->player_y - 1);
	else if (key == KEY_A)
		player_movements(game, game->map->player_x - 1, game->map->player_y);
	else if (key == KEY_S)
		player_movements(game, game->map->player_x, game->map->player_y + 1);
	else if (key == KEY_D)
		player_movements(game, game->map->player_x + 1, game->map->player_y);
	if (key == XK_Escape)
		free_game(game);
	return (0);
}
