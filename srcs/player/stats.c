/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stats.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 14:15:20 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/28 16:04:29 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	collect(t_game *game, t_collect **list, t_pos *pos)
{
	t_collect	*collect;

	collect = *list;
	while (collect)
	{
		if (collect->pos->x == pos->x && collect->pos->y == pos->y \
		&& collect->collected == false)
		{
			collect->collected = true;
			game->player->collectibles += 1;
			collect->img->enabled = false;
			break ;
		}
		collect = collect->next;
	}
}

bool	kill(t_enemy **list, t_pos *pos)
{
	t_enemy	*enemy;

	enemy = *list;
	while (enemy)
	{
		if (enemy->killed == false \
		&& enemy->pos->x == pos->x && enemy->pos->y == pos->y)
		{
			enemy->killed = true;
			enemy->img->enabled = false;
			return (true);
		}
		enemy = enemy->next;
	}
	return (false);
}

bool	take_damage(t_pos *pos, t_enemy **list)
{
	t_enemy			*enemy;

	enemy = *list;
	while (enemy)
	{
		if (enemy->killed == false \
		&& pos->x == enemy->pos->x && pos->y == enemy->pos->y)
			return (true);
		enemy = enemy->next;
	}
	return (false);
}

void	update_player_stats(t_game *game, t_player *player)
{
	if (player->lives == 0)
		player->status = DEAD;
	if (player->collectibles == game->map_info->collectible_count)
		game->exit_status = true;
}
