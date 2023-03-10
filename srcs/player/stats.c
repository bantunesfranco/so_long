/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stats.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 14:15:20 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/10 13:32:01 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			break ;
		}
		collect = collect->next;
	}
}

void	kill(t_game *game, t_enemy **list, char **map, t_pos *pos)
{
	t_enemy	*enemy;

	enemy = *list;
	while (enemy)
	{
		if (enemy->killed == false \
		&& enemy->pos->x == pos->x && enemy->pos->y == pos->y)
		{
			enemy->killed = true;
			break ;
		}
		enemy = enemy->next;
	}
}

bool	take_damage(t_player *player, t_enemy **list)
{
	t_enemy	*enemy;

	enemy = *list;
	while (enemy)
	{
		if (player->pos->x == enemy->pos->x && player->pos->y == enemy->pos->y)
		{
			player->lives -= 1;
			ft_printf("DAMAGE!!! %d\n", player->lives);
			return (true);
		}
		enemy = enemy->next;
	}
	return (false);
}

void	update_player_stats(t_game *game, t_player *player)
{
	if (take_damage(player, game->enemies) == true)
	{
		if (player->lives > 1)
			ft_printf("Damage\n");
		else
			ft_printf("Dead\n");
	}
}
