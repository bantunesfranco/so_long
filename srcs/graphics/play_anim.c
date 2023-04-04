/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   play_anim.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 11:21:58 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/31 17:38:06 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	move_sprite(t_player *player, t_dir move_dir)
{
	int			step;

	step = 1;
	if (move_dir == UP || move_dir == LEFT)
		step = -1;
	if (move_dir == LEFT || move_dir == RIGHT)
	{
		player->img->instances[0].x += (step * 4);
		player->dir = RIGHT;
		if (step == -1)
			player->dir = LEFT;
	}
	else if (move_dir == UP || move_dir == DOWN)
		player->img->instances[0].y += (step * 4);
}

static void	play_anim(t_game *game, t_player *player, uint8_t **arr, int i)
{
	int			dir;

	if (player->dir == LEFT)
		dir = 8;
	else
		dir = 0;
	player->img->pixels = arr[i + dir];
	if (player->status == WALK)
	{
		move_sprite(player, player->move_dir);
		if (player->move_dir == UP && !i)
			player->pos->y -= 1;
		if (player->move_dir == DOWN && !i)
			player->pos->y += 1;
		if (player->move_dir == LEFT && !i)
			player->pos->x -= 1;
		if (player->move_dir == RIGHT && !i)
			player->pos->x += 1;
		if (!i)
		{
			player->moves++;
			update_ui(game, game->ui, game->player);
		}
	}
	mlx_set_instance_depth(&player->img->instances[0], 5 + player->pos->y);
}

static void	end_check(t_game *game, t_player *player, int *i)
{
	*i = 0;
	if (game->player->status == DEAD || (game->exit_status == true \
	&& game->map[player->pos->y][player->pos->x] == 'E'))
		end_game(game);
	game->status = UNLOCKED;
	player->status = ALIVE;
}

void	update_anim(t_game *game, t_player *player)
{
	uint8_t		**sprites;
	int			frames;
	static int	i = 0;

	frames = 8;
	if (player->status == WALK)
		sprites = player->sprites[1];
	else if (player->status == ATK)
		sprites = player->sprites[2];
	else if (player->status == DMG)
	{
		frames = 3;
		sprites = player->sprites[3];
	}
	else if (player->status == DEAD)
		sprites = player->sprites[4];
	else
		return ;
	play_anim(game, player, sprites, i);
	i++;
	if (i == frames)
		end_check(game, player, &i);
}
