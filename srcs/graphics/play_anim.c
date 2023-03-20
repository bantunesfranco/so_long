/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   play_anim.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 11:21:58 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/20 18:02:31 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	play_anim(t_player *player, uint8_t **arr, int i)
{
	int		dir;

	if (player->dir == LEFT)
		dir = 8;
	else
		dir = 0;
	player->img->pixels = arr[i + dir];
}

void	update_anim(t_game *game, t_player *player)
{
	uint8_t		**sprites;
	int			frames;
	static int	i;

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
	{
		i = 0;
		game->status = UNLOCKED;
	}
}
