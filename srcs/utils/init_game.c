/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 09:17:48 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/10 11:44:22 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	add_collect(mlx_t *mlx, t_collect **list, int x, int y)
{
	t_collect			*collect;

	collect = ft_calloc(1, sizeof(t_collect));
	if (!collect)
		ft_error("so_long", ENOMEM);
	collect->pos = ft_calloc(1, sizeof(t_pos));
	if (!collect->pos)
		ft_error("so_long", ENOMEM);
	collect->pos->x = x;
	collect->pos->y = y;
	collect->collected = false;
	collect->next = NULL;
	collect->img = mlx_new_image(mlx, 48, 48);
	if (!*list)
		collect_add_back(list, collect);
	else
		collect_add_back(list, collect);
}

static void	add_enemy(mlx_t *mlx, t_enemy **list, int x, int y)
{
	t_enemy			*enemy;

	enemy = ft_calloc(1, sizeof(t_enemy));
	if (!enemy)
		ft_error("so_long", ENOMEM);
	enemy->pos = ft_calloc(1, sizeof(t_pos));
	if (!enemy->pos)
		ft_error("so_long", ENOMEM);
	enemy->pos->x = x;
	enemy->pos->y = y;
	enemy->killed = false;
	enemy->next = NULL;
	enemy->img = mlx_new_image(mlx, 48, 48);
	if (!*list)
		enemy_add_back(list, enemy);
	else
		enemy_add_back(list, enemy);
}

static void	init_pois(t_game *game, char **map)
{
	int	i;
	int	j;

	game->collectibles = ft_calloc(1, sizeof(t_collect *));
	if (!game->collectibles)
		ft_error("so_long", ENOMEM);
	game->enemies = ft_calloc(1, sizeof(t_enemy *));
	if (!game->enemies)
		ft_error("so_long", ENOMEM);
	i = -1;
	while (++i < game->map_info->rows)
	{
		j = -1;
		while (++j < game->map_info->cols)
		{
			if (map[i][j] == 'C')
				add_collect(game->mlx, game->collectibles, j, i);
			if (map[i][j] == 'K')
				add_enemy(game->mlx, game->enemies, j, i);
		}
	}
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
	player->dir = 0;
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
	game->player->img = mlx_new_image(game->mlx, 48, 48);
	init_pois(game, game->map);
	game->map_tiles = ft_calloc(game->map_info->size, sizeof(mlx_image_t *));
	if (!game->map_tiles)
		ft_error("so_long", ENOMEM);
	game->status = true;
	game->exit_status = false;
	game->time = 0;
}