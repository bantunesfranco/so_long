/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stats.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 14:15:20 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/13 18:02:46 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

bool	collect(t_game *game, t_collect **list, char **map, t_pos *pos)
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
			ft_printf("New Collect\n");
			return (true);
		}
		collect = collect->next;
	}
	return (false);
}

bool	kill(t_game *game, t_enemy **list, char **map, t_pos *pos)
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
			ft_printf("HADOUKEN!!\n");
			return (true);
		}
		enemy = enemy->next;
	}
	return (false);
}

bool	take_damage(t_player *player, t_enemy **list)
{
	t_enemy			*enemy;
	static t_pos	pos[1] = {-1, -1};

	enemy = *list;
	if (pos->x == player->pos->x && pos->y == player->pos->y)
		return (false);
	while (enemy)
	{
		if (player->pos->x == enemy->pos->x && player->pos->y == enemy->pos->y)
		{
			ft_printf("%d\n", player->lives);
			player->lives -= 1;
			ft_printf("%d\n", player->lives);
			pos->x = player->pos->x;
			pos->y = player->pos->y;
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
		if (player->lives >= 1)
			ft_printf("Damage\n");
		else
			ft_printf("Dead\n");
	}
}
