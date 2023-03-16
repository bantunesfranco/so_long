/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/20 09:51:07 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/16 14:50:02 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>
#include <MLX42/MLX42_Input.h>

static bool	is_valid_coord(int32_t x, int32_t y, t_map *info, char **map)
{
	if (!(x >= 0 && x < info->cols - 1 && y > 0 && y <= info->rows - 1))
		return (false);
	if (map[y][x] == '1')
		return (false);
	return (true);
}

static void	move_sprite(t_player *player, int32_t coord, char xy, int step)
{
	// double	time;
	int		i;
	int		j;

	i = 0;
	j = 0;
	// time = mlx_get_time();
	if (xy == 'x')
		player->pos->x += step;
	else if (xy == 'y')
		player->pos->y += step;
	if (xy == 'x')
	{
		player->img->instances[0].x += (32 * step);
		if (step < 0)
			player->dir = 2;
		else
			player->dir = 3;
		// time = mlx_get_time();
	}
	else if (xy == 'y')
	{
		player->img->instances[0].y += (32 * step);
		// time = mlx_get_time();
	}
}

static void	can_move(t_player *player, t_game *game, int32_t dir)
{
	int32_t	x;
	int32_t	y;

	x = player->pos->x;
	y = player->pos->y;
	if (dir == UP && game->status != LOCKED)
	{
		if (is_valid_coord(x, y - 1, game->map_info, game->map) == true)
			move_sprite(player, y, 'y', -1);
	}
	else if (dir == DOWN && game->status != LOCKED)
	{
		if (is_valid_coord(x, y + 1, game->map_info, game->map) == true)
			move_sprite(player, y, 'y', 1);
	}
	else if (dir == LEFT && game->status != LOCKED)
	{
		if (is_valid_coord(x - 1, y, game->map_info, game->map) == true)
			move_sprite(player, x, 'x', -1);
	}
	else if (dir == RIGHT && game->status != LOCKED)
	{
		if (is_valid_coord(x + 1, y, game->map_info, game->map) == true)
			move_sprite(player, x, 'x', 1);
	}
}

static void	move(mlx_key_data_t k, void *param)
{
	mlx_t			*mlx;
	t_game			*game;
	static int		time;

	game = param;
	mlx = game->mlx;
	if (!time)
		time = mlx_get_time();
	if (mlx_get_time() - time > 0.5)
	{
		if ((k.key == MLX_KEY_W || k.key == MLX_KEY_UP) && k.action == MLX_PRESS)
			can_move(game->player, game, UP);
		if ((k.key == MLX_KEY_S || k.key == MLX_KEY_DOWN) && k.action == MLX_PRESS)
			can_move(game->player, game, DOWN);
		if ((k.key == MLX_KEY_A || k.key == MLX_KEY_LEFT) && k.action == MLX_PRESS)
			can_move(game->player, game, LEFT);
		if ((k.key == MLX_KEY_D || k.key == MLX_KEY_RIGHT) && k.action == MLX_PRESS)
			can_move(game->player, game, RIGHT);
		time = mlx_get_time();
	}
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
			if (collect(game, game->collectibles, game->map, &newpos) == true)
			{	
				ft_printf("collected = %d\n", game->player->collectibles);
				break ;
			}
		}
		i++;
	}
}

static void	attack(t_game *game)
{
	int			i;
	t_pos		*pos;
	t_pos		newpos;
	const int	dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

	i = 0;
	pos = game->player->pos;
	while (i < 4)
	{
		newpos.x = pos->x + dir[i][0];
		newpos.y = pos->y + dir[i][1];
		if (game->map[newpos.y][newpos.x] == 'K')
		{
			if (kill(game, game->enemies, game->map, &newpos) == true)
				break ;
		}
		i++;
	}
	// play_anim(game->player, game->player->sprites[2], 8);
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
		attack(game);
	else if (k.key == MLX_KEY_ESCAPE && k.action == MLX_PRESS)
		exit_game(game);
	else
		move(k, param);
	// else if (k.key == MLX_KEY_R && k.action == MLX_PRESS)
	// 	restart_game(game);
}
