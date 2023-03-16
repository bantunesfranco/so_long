/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 09:17:48 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/16 12:44:37 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	add_collect(mlx_t *mlx, t_collect **list, \
						uint8_t **arr, t_pos *pos)
{
	t_collect			*collect;

	collect = ft_calloc(1, sizeof(t_collect));
	if (!collect)
		ft_error("so_long", ENOMEM);
	collect->pos = ft_calloc(1, sizeof(t_pos));
	if (!collect->pos)
		ft_error("so_long", ENOMEM);
	collect->pos->x = pos->x;
	collect->pos->y = pos->y;
	collect->collected = false;
	collect->next = NULL;
	collect->img = mlx_new_image(mlx, 48, 48);
	collect->sprites = arr;
	if (!*list)
		collect_add_back(list, collect);
	else
		collect_add_back(list, collect);
}

static void	add_enemy(mlx_t *mlx, t_enemy **list, \
						uint8_t **arr, t_pos *pos)
{
	t_enemy			*enemy;

	enemy = ft_calloc(1, sizeof(t_enemy));
	if (!enemy)
		ft_error("so_long", ENOMEM);
	enemy->pos = ft_calloc(1, sizeof(t_pos));
	if (!enemy->pos)
		ft_error("so_long", ENOMEM);
	enemy->pos->x = pos->x;
	enemy->pos->y = pos->y;
	enemy->killed = false;
	enemy->next = NULL;
	enemy->img = mlx_new_image(mlx, 48, 48);
	enemy->dir = RIGHT;
	enemy->sprites = arr;
	if (!*list)
		enemy_add_back(list, enemy);
	else
		enemy_add_back(list, enemy);
}

static void	init_pois(t_game *game, char **map)
{
	t_pos			pos;
	// uint8_t			**sprites;
	mlx_texture_t	*text;
	uint8_t			**sprites2;

	text = mlx_load_png("./sprites/ghost48.png");
	// sprites = ft_calloc(1, sizeof(mlx_texture_t *));
	sprites2 = ft_calloc(1, sizeof(uint8_t *));
	if (!sprites2 || !sprites2)
		ft_error("so_long", ENOMEM);
	// sprites = load_poi_anim(game, text, 12, 0);
	sprites2 = load_poi_anim(game, text, 12, 0);
	pos.y = -1;
	while (++pos.y < game->map_info->rows)
	{
		pos.x = -1;
		while (++pos.x < game->map_info->cols)
		{
			if (map[pos.y][pos.x] == 'C')
				add_collect(game->mlx, game->collectibles, sprites2, &pos);
			if (map[pos.y][pos.x] == 'K')
				add_enemy(game->mlx, game->enemies, sprites2, &pos);
		}
	}
	mlx_delete_texture(text);
}

static void	init_player(t_game *game)
{
	t_player	*player;
	t_pos		*start_pos;
	t_pos		*pos;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		ft_error("so_long", ENOMEM);
	player->start_pos = ft_calloc(1, sizeof(t_pos));
	if (!player->start_pos)
		ft_error("so_long", ENOMEM);
	player->pos = ft_calloc(1, sizeof(t_pos));
	if (!player->pos)
		ft_error("so_long", ENOMEM);
	player->lives = 3;
	player->dir = RIGHT;
	player->collectibles = 0;
	player->start_pos->x = 0;
	player->start_pos->y = 0;
	player->moves = 0;
	game->player = player;
}

void	init_game(t_game *game, char **argv)
{
	init_player(game);
	game->map = map_parser(argv[1], game);
	game->width = SIZE * game->map_info->cols + 500;
	game->height = SIZE * game->map_info->rows + 500;
	game->mlx = mlx_init(game->width, game->height, "so_long", true);
	if (!game->mlx)
		exit(EXIT_FAILURE);
	game->collectibles = ft_calloc(1, sizeof(t_collect *));
	game->enemies = ft_calloc(1, sizeof(t_enemy *));
	if (!game->collectibles || !game->enemies)
		ft_error("so_long", ENOMEM);
	game->player->img = mlx_new_image(game->mlx, 48, 48);
	init_pois(game, game->map);
	game->map_tiles = ft_calloc(game->map_info->size, sizeof(mlx_image_t *));
	if (!game->map_tiles)
		ft_error("so_long", ENOMEM);
	game->status = true;
	game->exit_status = false;
	game->time = 0;
}
