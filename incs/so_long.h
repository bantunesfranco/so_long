/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 13:25:13 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/14 10:56:17 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include "libft.h"
# include <MLX42/MLX42.h>

# define SIZE 32

typedef enum e_dir
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
}	t_dir;

typedef struct s_pos
{
	int32_t	x;
	int32_t	y;
}	t_pos;

typedef struct s_collect
{
	bool				collected;
	mlx_image_t			*img;
	mlx_texture_t		**sprites;
	t_pos				*pos;
	struct s_collect	*next;
}	t_collect;

typedef struct s_enemy
{
	bool			killed;
	mlx_image_t		*img;
	mlx_texture_t	**sprites;
	t_pos			*pos;
	t_dir			dir;
	struct s_enemy	*next;
}	t_enemy;

typedef struct s_player
{
	mlx_image_t		*img;
	mlx_texture_t	***sprites;
	int32_t			dir;
	int				lives;
	int32_t			collectibles;
	int32_t			moves;
	t_pos			*pos;
	t_pos			*start_pos;
	bool			locked;
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
	double		time;
	bool		status;
	bool		exit_status;
}	t_game;

void			init_game(t_game *game, char **argv);
void			enemy_add_back(t_enemy **lst, t_enemy *new);
void			collect_add_back(t_collect **lst, t_collect *new);

void			render_walls(t_game *game, int x, int y);
void			render_map(t_game *game, char **map);
void			render_player(t_game *game, t_player *player);

void			update_player_stats(t_game *game, t_player *player);
void			update_player(t_player *player);
bool			collect(t_game *game, t_collect **list, char **map, t_pos *pos);
bool			kill(t_game *game, t_enemy **list, char **map, t_pos *pos);
bool			take_damage(t_player *player, t_enemy **list);
void			interactions(mlx_key_data_t k, void *param);
void			draw_player(void *param);

void			free_info(t_map *info);
bool			can_exit(char **map, t_map *info, t_pos *pos);
bool			validate_map(char **map, t_map	*info, t_game *game);

void			ft_free_int_arr(int **arr, int size);
char			**map_parser(char *map, t_game *game);
mlx_texture_t	*load_spritesheet(mlx_t *mlx, char *file);

void			load_player_anim(t_game *game, mlx_texture_t *txt, \
int frames, int y);
mlx_texture_t	*mlx_texture_area_to_texture(mlx_texture_t *texture, \
uint32_t xy[2], uint32_t wh[2]);
void			clear_spritelist(t_game *game, mlx_image_t **arr);

#endif