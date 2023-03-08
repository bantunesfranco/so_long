/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 13:25:13 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/08 10:20:01 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <math.h>
# include <stdlib.h>
# include "../libft/incs/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define SIZE 32

typedef struct s_pos
{
	int32_t	x;
	int32_t	y;
}	t_pos;

typedef struct s_collect
{
	bool				collected;
	t_pos				*pos;
	struct s_collect	*next;
}	t_collect;

typedef struct s_enemy
{
	bool			killed;
	t_pos			*pos;
	struct s_enemy	*next;
}	t_enemy;

typedef struct s_player
{
	mlx_image_t	*sprite;
	int32_t		dir;
	int32_t		lives;
	int32_t		collectibles;
	t_pos		*pos;
	t_pos		*start_pos;
	bool		locked;
}	t_player;

typedef struct s_map
{
	int32_t	rows;
	int32_t	cols;
	int32_t	size;
	int32_t	player_count;
	int32_t	exit_count;
	int32_t	collectible_count;
	int32_t	**visited;
	t_pos	*queue;
}	t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map_info;
	char		**map;
	int32_t		width;
	int32_t		height;
	t_player	*player;
	t_enemy		**enemies;
	t_collect	**collectibles;
	mlx_image_t	**map_tiles;
	int			moves;
	double		time;
	bool		status;
	bool		exit_status;
}	t_game;

void			init_game(t_game *game, char **argv);

void			render_walls(t_game *game, int x, int y);
void			render_map(t_game *game, char **map);
void			render_player(t_game *game, t_player *player);

void			collect(t_game *game, t_collect **list, char **map, t_pos *pos);
void			interactions(mlx_key_data_t k, void *param);
void			draw_player(void *param);

void			free_info(t_map *info);
bool			can_exit(char **map, t_map *info, t_pos *pos);
bool			validate_map(char **map, t_map	*info, t_game *game);

void			ft_free_int_arr(int **arr, int size);
char			**map_parser(char *map, t_game *game);
mlx_texture_t	*load_spritesheet(mlx_t *mlx, char *file);

void			clear_spritelist(t_game *game, mlx_image_t **arr);

#endif