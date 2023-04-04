/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/20 09:51:07 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/31 14:44:03 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>
#include <MLX42/MLX42_Input.h>

static bool	is_valid_coord(int32_t x, int32_t y, t_game *game, char **map)
{
	const t_pos	pos = {x, y};

	if (!(x >= 0 && x < game->map_info->cols - 1 \
	&& y > 0 && y <= game->map_info->rows - 1))
		return (false);
	if (map[y][x] == '1')
		return (false);
	game->status = LOCKED;
	if (take_damage((t_pos *)&pos, game->enemies) == true)
	{
		game->player->status = DMG;
		game->player->lives--;
		update_ui(game, game->ui, game->player);
		return (false);
	}
	game->player->status = WALK;
	return (true);
}

static void	can_move(t_player *player, t_game *game, int32_t dir)
{
	int32_t	x;
	int32_t	y;

	x = player->pos->x;
	y = player->pos->y;
	if (dir == UP && game->status != LOCKED)
	{
		if (is_valid_coord(x, y - 1, game, game->map) == true)
			player->move_dir = UP;
	}
	else if (dir == DOWN && game->status != LOCKED)
	{
		if (is_valid_coord(x, y + 1, game, game->map) == true)
			player->move_dir = DOWN;
	}
	else if (dir == LEFT && game->status != LOCKED)
	{
		if (is_valid_coord(x - 1, y, game, game->map) == true)
			player->move_dir = LEFT;
	}
	else if (dir == RIGHT && game->status != LOCKED)
	{
		if (is_valid_coord(x + 1, y, game, game->map) == true)
			player->move_dir = RIGHT;
	}
}

static void	move(mlx_key_data_t k, void *param)
{
	t_game			*game;

	game = param;
	if (game->status != LOCKED)
	{
		if ((k.key == MLX_KEY_W || k.key == MLX_KEY_UP) \
		&& k.action == MLX_PRESS)
			can_move(game->player, game, UP);
		else if ((k.key == MLX_KEY_S || k.key == MLX_KEY_DOWN) \
		&& k.action == MLX_PRESS)
			can_move(game->player, game, DOWN);
		else if ((k.key == MLX_KEY_A || k.key == MLX_KEY_LEFT) \
		&& k.action == MLX_PRESS)
			can_move(game->player, game, LEFT);
		else if ((k.key == MLX_KEY_D || k.key == MLX_KEY_RIGHT) \
		&& k.action == MLX_PRESS)
			can_move(game->player, game, RIGHT);
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
			if (kill(game->enemies, &newpos) == true)
				break ;
		}
		i++;
	}
	game->status = LOCKED;
	game->player->status = ATK;
}

void	interactions(mlx_key_data_t k, void *param)
{
	t_game	*game;

	game = param;
	if (game->status == UNLOCKED)
	{
		if (k.key == MLX_KEY_SPACE && k.action == MLX_PRESS)
			attack(game);
		else if (k.key == MLX_KEY_R && k.action == MLX_PRESS)
			restart_game(game);
		else if (k.key == MLX_KEY_ESCAPE && k.action == MLX_PRESS)
			exit_game(game);
		else
			move(k, param);
	}
}
