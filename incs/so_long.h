/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 13:25:13 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/30 16:43:31 by bfranco       ########   odam.nl         */
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
# define PADX 640
# define PADY 160
# define ARG "so_long: Invalid number of arguments.\n\
Use: ./so_long [path_to_map]"
# define CMDS "Arrow keys or WASD to move\n\
R to restart\n\
SPACE to attack\n\
ESC to exit game"

typedef enum e_status
{
	ALIVE = 0,
	DEAD = 1,
	WALK = 2,
	ATK = 3,
	DMG = 4,
	CAN_EXIT = 5,
	LOCKED = 6,
	UNLOCKED = 7,
	RESTART = 8,
	END = 9,
}	t_status;

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
	uint8_t				**sprites;
	t_pos				*pos;
	struct s_collect	*next;
}	t_collect;

typedef struct s_enemy
{
	bool			killed;
	mlx_image_t		*img;
	uint8_t			**sprites;
	t_pos			*start_pos;
	t_pos			*pos;
	t_dir			dir;
	t_dir			move_dir;
	struct s_enemy	*next;
}	t_enemy;

typedef struct s_player
{
	mlx_image_t		*img;
	uint8_t			***sprites;
	t_dir			dir;
	t_dir			move_dir;
	int32_t			lives;
	int32_t			collectibles;
	int32_t			moves;
	t_pos			*pos;
	t_pos			*start_pos;
	t_status		status;
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

typedef struct s_ui
{
	mlx_image_t	*lives;
	mlx_image_t	*col;
	mlx_image_t	*moves;
	mlx_image_t	*nb_m;
	mlx_image_t	*nb_c;
	mlx_image_t	*nb_l;
	mlx_image_t	*total;
	mlx_image_t	*background;
	mlx_image_t	*end;
	mlx_image_t	*end_msg;
}	t_ui;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map_info;
	char		**map;
	t_ui		*ui;
	int32_t		width;
	int32_t		height;
	t_player	*player;
	t_enemy		**enemies;
	t_collect	**collectibles;
	double		time;
	t_status	status;
	bool		exit_status;
}	t_game;

/* init game*/
void			init_game(t_game *game, char **argv);
void			enemy_add_back(t_enemy **lst, t_enemy *new);
void			collect_add_back(t_collect **lst, t_collect *new);

/* map parsing*/
char			**map_parser(char *map, t_game *game);
bool			validate_map(char **map, t_map	*info, t_game *game);
bool			can_exit(char **map, t_map *info, t_pos *pos);

/* graphics */
void			render_walls(t_game *game, int x, int y);
void			render_map(t_game *game, char **map);
void			render_player(t_game *game, t_player *player);

/* ui */
void			render_ui(t_game *game, t_ui *ui, t_player *player);
void			update_ui(t_game *game, t_ui *ui, t_player *player);
void			end_screen(t_game *game, t_ui *ui, char *str);

/* pixel buffers*/
uint8_t			**load_poi_anim(mlx_texture_t *txt, int frames, \
								int y, char type);
uint8_t			**load_player_anim(mlx_texture_t *txt, \
								int frames, int y);
uint8_t			*split_text(mlx_texture_t *text, uint32_t xy[2], \
							uint32_t wh[2]);

/* animations */
void			draw_player(void *param);
void			update_player(t_player *player);
void			render_enemies(t_game *game, int x, int y);
void			update_enemy(t_enemy **list);
void			render_collectibles(t_game *game, int x, int y);
void			update_collectible(t_collect **list);
void			update_anim(t_game *game, t_player *player);

/* game interations */
void			interactions(mlx_key_data_t k, void *param);
void			collect(t_game *game, t_collect **list, t_pos *pos);
bool			kill(t_enemy **list, t_pos *pos);
void			move_sprite(t_player *player, t_dir move_dir);

/* update game state */
bool			take_damage(t_pos *pos, t_enemy **list);
void			update_player_stats(t_game *game, t_player *player);
void			exit_game(t_game *game);
void			restart_game(t_game *game);
void			end_game(t_game *game);
float			delay(t_player *player);

/* cleanup */
void			free_info(t_map *info);
void			ft_free_int_arr(int **arr, int size);

#endif