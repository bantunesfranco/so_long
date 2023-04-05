/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_poi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:37:21 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/30 13:33:28 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	update_enemy(t_enemy **list)
{
	static int		iter = 0;
	static double	time = 0;
	int				dir;
	t_enemy			*head;

	if (!list)
		return ;
	head = *list;
	if (mlx_get_time() - time > 0.15)
	{
		while (head)
		{
			if (head->dir == LEFT)
				dir = 6;
			else
				dir = 0;
			head->img->pixels = head->sprites[iter % 6 + dir];
			head = head->next;
		}
		time = mlx_get_time();
		iter++;
	}
}

void	update_collectible(t_collect **list)
{
	static int		iter;
	static double	time;
	t_collect		*head;

	if (!list)
		return ;
	head = *list;
	if (mlx_get_time() - time > 0.15)
	{
		while (head)
		{
			head->img->pixels = head->sprites[iter % 4];
			head = head->next;
		}
		time = mlx_get_time();
		iter++;
	}
}

void	render_collectibles(t_game *game, int x, int y)
{
	t_collect		*head;

	if (!game->collectibles)
		return ;
	head = *game->collectibles;
	while (head)
	{
		if (head->pos->x == x && head->pos->y == y)
		{
			head->img->pixels = head->sprites[0];
			break ;
		}
		head = head->next;
	}
	mlx_image_to_window(game->mlx, head->img, \
	SIZE * x + PADX / 8, SIZE * y + PADY / 2);
	mlx_set_instance_depth(&head->img->instances[0], 3);
}

void	render_enemies(t_game *game, int x, int y)
{
	t_enemy			*head;

	if (!game->enemies)
		return ;
	head = *game->enemies;
	while (head)
	{
		if (head->pos->x == x && head->pos->y == y)
		{
			head->img->pixels = head->sprites[0];
			break ;
		}
		head = head->next;
	}
	mlx_image_to_window(game->mlx, head->img, \
	SIZE * x + PADX / 8, SIZE * y + PADY / 2 - 20);
	mlx_set_instance_depth(&head->img->instances[0], 4 + y);
}
