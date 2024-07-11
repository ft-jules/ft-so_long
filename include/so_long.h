/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:01:31 by jpointil          #+#    #+#             */
/*   Updated: 2024/07/09 18:34:27 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define INT_MAX_STRING "2147483647"
# define INT_MIN_STRING "-2147483648"
# define TILE_PIXELS 32
# define BUFFERSIZE 10000

# define VISITED_SPAWN 7
# define VISITED_TILE 6
# define COLLECTED_COLLECTIBLE 8

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define ESC 65307
# define ESC2 33

# define J "please retry"

/*----------COLORS-----------*/

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

/*----------STRUCT----------*/

typedef struct s_sprites
{
	void		*player;
	void		*collectibles;
	void		*floor;
	void		*wall;
	void		*exit;
	void		*opened_exit;
	void		*collected_collectibles;
}				t_sprites;

typedef struct s_map
{
	int			height;
	int			width;
	int			collectibles;
	int			collected;
	bool		player;
	int			player_x;
	int			player_y;
	bool		exit;
	int			exit_y;
	int			exit_x;
	bool		accessible_exit;
	char		*big_line;
	char		**tiles;

}				t_map;

typedef struct s_game
{
	t_map		*map;
	t_sprites	*sprites;
	void		*mlx;
	void		*mlx_win;
	int			size;
	int			steps;
}				t_game;

typedef enum s_type
{
	R,
	MAP,
	SPRITE,
	GAME
}				t_type;

/*---------FUNCTIONS--------*/

// MAP FUNCTIONS

t_map			*map_init(char *path);
void			check_map_is_playable(t_map *map);
void			check_big_line(const char *str, t_map *map);
void			free_map(t_map *map);
void			print_map(char **map);
void			map_error(t_map *map, char *message, char flag);

// GAME FUNCTIONS

void			game_error(void *ptr, t_type type, char *message);
void			game_init(t_game *game, char *path);
void			sprites_init(t_game *game);
void			render_map(t_game *game, int x, int y);
void			free_game(t_game *game);
int				key_handler(int key, t_game *game);

#endif