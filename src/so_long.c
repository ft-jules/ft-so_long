/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:37:12 by jpointil          #+#    #+#             */
/*   Updated: 2024/07/09 18:46:13 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	check_big_line(const char *str, t_map *map)
{
	while (*str)
	{
		if (*str == '\n' && *(str + 1) == '\n')
			game_error((void *)map, MAP, "please provide a correct map");
		str++;
	}
	return ;
}

int	close_game(t_game *game)
{
	free_game(game);
	return (0);
}

void	init_struct(t_game *game)
{
	game->sprites = NULL;
	game->mlx_win = NULL;
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf(RED "GameError : Mlx failed to open\n");
		free_game(game);
		return ;
	}
	game->mlx_win = mlx_new_window(game->mlx, game->map->width * 32,
			game->map->height * 32, "42SO_LONG <333");
	if (!game->mlx_win)
	{
		ft_printf(RED "GameError : Mlx failed to open\n");
		free_game(game);
		return ;
	}
	sprites_init(game);
	render_map(game, 0, 0);
	game->steps = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf(RED "Usage: %s <map_dir>/<map_file>\n" RESET, argv[0]);
		return (0);
	}
	game.map = map_init(argv[1]);
	init_struct(&game);
	mlx_hook(game.mlx_win, KeyPress, KeyPressMask, key_handler, &game);
	mlx_hook(game.mlx_win, DestroyNotify, 0, &close_game, &game);
	mlx_loop(game.mlx);
	free_game(&game);
}
