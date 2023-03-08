/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stats.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 14:15:20 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/08 10:21:52 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

void	collect(t_game *game, t_collect **list, char **map, t_pos *pos)
{
	t_collect	*collect;

	collect = *list;
	while (collect)
	{
		if (collect->collected == false \
		&& collect->pos->x == pos->x && collect->pos->y == pos->y)
		{
			collect->collected = true;
			game->player->collectibles += 1;
		}
		collect = collect->next;
	}
}

void	take_damage(t_player *player, t_enemy **list)
{
	t_enemy	*enemy;

	enemy = *list;
	while (enemy)
	{
		if (player->pos->x == enemy->pos->x && player->pos->y == enemy->pos->y)
		{
			player->lives -= 1;
			ft_printf("DAMAGE!!! %d\n", player->lives);
			break ;
		}
		enemy = enemy->next;
	}
}
