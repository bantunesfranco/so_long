/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   play_anim.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 11:21:58 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/23 17:53:55 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	move_sprite(t_player *player, t_dir move_dir)
{
	int			step;
	static int	moved = 0;

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
	moved += 4;
	if (moved == 32)
		moved = 0;
	// ft_printf("%d %d %d\n", player->pos->x, player->pos->y, player->move_dir);
}

static void	play_anim(t_player *player, uint8_t **arr, int i)
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
			ft_printf("moves %d\n", player->moves);
		}
	}
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
	play_anim(player, sprites, i);
	i++;
	if (i == frames)
		end_check(game, player, &i);
}
