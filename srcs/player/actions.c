/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/20 09:51:07 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/08 09:51:30 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/so_long.h"

static bool	is_valid_coord(t_pos *new, t_map *info, char **map)
{
	int	x;
	int	y;

	x = new->x;
	y = new->y;
	if ((x >= 0 && x < info->cols - 1 && y > 0 && y <= info->rows - 1))
		return (true);
	return (false);
}

static void	move_sprite(t_player *player, int32_t coord, char xy, int step)
{
	double	time;
	int		i;
	int		j;

	i = 0;
	j = 0;
	player->lives = true;
	time = mlx_get_time();
	if (xy == 'x')
		player->pos->x += step;
	else if (xy == 'y')
		player->pos->y += step;
	if (xy == 'x')
	{
		player->sprite->instances[0].x += (32 * step);
		time = mlx_get_time();
	}
	else if (xy == 'y')
	{
		player->sprite->instances[0].y += (32 * step);
		time = mlx_get_time();
	}
}

static void	can_move(t_player *player, t_game *game, int dir)
{
	t_pos	*pos;

	pos = player->pos;
	if (dir == 0 && player->locked == false)
	{
		if (is_valid_coord(pos, game->map_info, game->map) == true \
		&& game->map[pos->y - 1][pos->x] != '1')
			move_sprite(player, pos->y, 'y', -1);
	}
	else if (dir == 1 && player->locked == false)
	{
		if (is_valid_coord(pos, game->map_info, game->map) == true \
		&& game->map[pos->y + 1][pos->x] != '1')
			move_sprite(player, pos->y, 'y', 1);
	}
	else if (dir == 2 && player->locked == false)
	{
		if (is_valid_coord(pos, game->map_info, game->map) == true \
		&& game->map[pos->y][pos->x - 1] != '1')
			move_sprite(player, pos->x, 'x', -1);
	}
	else if (dir == 3 && player->locked == false)
	{
		if (is_valid_coord(pos, game->map_info, game->map) == true \
		&& game->map[pos->y][pos->x + 1] != '1')
			move_sprite(player, pos->x, 'x', 1);
	}
	player->locked = false;
	// ft_printf("(%d, %d)\n", player->pos->x, player->pos->y);
}

static void	move(mlx_key_data_t k, void *param)
{
	mlx_t			*mlx;
	t_game			*game;

	game = param;
	mlx = game->mlx;
	if ((k.key == MLX_KEY_W || k.key == MLX_KEY_UP) && k.action == MLX_PRESS)
		can_move(game->player, game, 0);
	if ((k.key == MLX_KEY_S || k.key == MLX_KEY_DOWN) && k.action == MLX_PRESS)
		can_move(game->player, game, 1);
	if ((k.key == MLX_KEY_A || k.key == MLX_KEY_LEFT) && k.action == MLX_PRESS)
		can_move(game->player, game, 2);
	if ((k.key == MLX_KEY_D || k.key == MLX_KEY_RIGHT) && k.action == MLX_PRESS)
		can_move(game->player, game, 3);
}

static void	open_chest(t_game *game)
{
	t_pos		*pos;
	t_pos		newpos;
	const int	dir[5][2] = {{0, 0}, {0, -1}, {0, 1}, {-1, 0}, {1, 0}};
	int			i;

	i = 0;
	pos = game->player->pos;
	while (i < 5)
	{
		newpos.x = pos->x + dir[i][0];
		newpos.y = pos->y + dir[i][1];
		if (game->map[newpos.y][newpos.x] == 'C')
		{	
			ft_printf("Insert zelda collectible sound...\n");
			collect(game, game->collectibles, game->map, &newpos);
			ft_printf("collect = %d\n", game->player->collectibles);
		}
		i++;
	}
}

void	interactions(mlx_key_data_t k, void *param)
{
	mlx_t	*mlx;
	t_game	*game;

	game = param;
	mlx = game->mlx;
	if (k.key == MLX_KEY_E && k.action == MLX_PRESS)
		open_chest(game);
	else if (k.key == MLX_KEY_SPACE && k.action == MLX_PRESS)
		ft_printf("HADOUKEN!!!\n");
	// 	player_attack();
	else if (k.key == MLX_KEY_ESCAPE && k.action == MLX_PRESS)
		mlx_close_window(mlx);
	else
		move(k, param);
}
