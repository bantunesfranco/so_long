/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 16:20:12 by bfranco       #+#    #+#                 */
/*   Updated: 2023/04/05 15:35:17 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	reset_player(t_player *player)
{
	t_pos			*pos;
	mlx_image_t		*img;

	img = player->img;
	pos = player->start_pos;
	ft_memcpy(player->pos, player->start_pos, sizeof(t_pos *));
	img->enabled = false;
	img->pixels = player->sprites[0][0];
	img->instances[0].x = SIZE * pos->x + PADX / 8 - 5;
	img->instances[0].y = SIZE * (pos->y - 1) + PADY / 2 + 5;
	player->lives = 3;
	player->collectibles = 0;
	player->moves = 0;
	img->enabled = true;
}

static void	reset_enemies(t_enemy **list)
{
	t_pos			*pos;
	mlx_image_t		*img;
	t_enemy			*head;

	if (!list)
		return ;
	head = *list;
	while (head)
	{
		img = head->img;
		pos = head->start_pos;
		ft_memcpy(head->pos, pos, sizeof(t_pos *));
		img->enabled = false;
		img->pixels = head->sprites[0];
		img->instances[0].x = SIZE * pos->x + PADX / 8;
		img->instances[0].y = SIZE * pos->y + PADY / 2 - 20;
		head->killed = false;
		head->dir = 3;
		img->enabled = true;
		head = head->next;
	}
}

static void	reset_collectibles(t_collect **list)
{
	mlx_image_t		*img;
	t_collect		*head;

	if (!list)
		return ;
	head = *list;
	while (head)
	{
		img = head->img;
		img->enabled = false;
		img->pixels = head->sprites[0];
		head->collected = false;
		img->enabled = true;
		head = head->next;
	}
}

void	restart_game(t_game *game)
{
	reset_player(game->player);
	reset_enemies(game->enemies);
	reset_collectibles(game->collectibles);
	update_ui(game, game->ui, game->player);
	ft_printf("Restarting...\n");
}
