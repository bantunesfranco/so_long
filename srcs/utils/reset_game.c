/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 16:20:12 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/17 11:10:34 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	reset_player(t_game *game, t_player *player)
{
	t_pos			*pos;
	mlx_image_t		*img;

	img = player->img;
	pos = player->start_pos;
	ft_memcpy(player->pos, player->start_pos, sizeof(t_pos *));
	img->enabled = false;
	img->pixels = player->sprites[0][0];
	img->instances[0].x = SIZE * pos->x + \
	(game->width - game->map_info->cols * SIZE) / 2 - 155;
	img->instances[0].y = SIZE * pos->y + \
	(game->height - game->map_info->rows * SIZE) / 2 - 20;
	player->lives = 3;
	player->collectibles = 0;
	img->enabled = true;
}

static void	reset_enemies(t_game *game, t_enemy **list)
{
	t_pos			*pos;
	mlx_image_t		*img;
	t_enemy			*head;

	head = *list;
	while (head)
	{
		img = head->img;
		pos = head->start_pos;
		ft_memcpy(head->pos, pos, sizeof(t_pos *));
		img->enabled = false;
		img->pixels = head->sprites[0];
		img->instances[0].x = SIZE * pos->x + \
		(game->width - game->map_info->cols * SIZE) / 2 - 155;
		img->instances[0].y = SIZE * pos->y + \
		(game->height - game->map_info->rows * SIZE) / 2 - 20;
		head->killed = false;
		head->dir = 3;
		img->enabled = true;
		head = head->next;
	}
}

void	restart_game(t_game *game)
{
	ft_printf("RESTART!!!!!!!!");
	reset_player(game, game->player);
	reset_enemies(game, game->enemies);
	// reset_collectibles(game->collectibles);
	// exit_game(game);
	return ;
}
