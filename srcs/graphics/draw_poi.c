/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_poi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:37:21 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/17 11:47:29 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	update_enemy(t_enemy **list)
{
	static int		iter;
	static double	time;
	int				dir;
	t_enemy			*head;

	head = *list;
	if (mlx_get_time() - time > 0.15)
	{
		while (head)
		{
			if (head->dir == 2)
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

void	render_collectibles(t_game *game, int x, int y)
{
	t_collect		*head;

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
	SIZE * x + (game->width - game->map_info->cols * SIZE) / 2 - 150, \
	SIZE * (y - 1) + (game->height - game->map_info->rows * SIZE) / 2 - 20);
	// mlx_set_instance_depth(&img->instances[0], 3);
}

void	render_enemies(t_game *game, int x, int y)
{
	t_enemy			*head;

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
	SIZE * x + (game->width - game->map_info->cols * SIZE) / 2 - 150, \
	SIZE * y + (game->height - game->map_info->rows * SIZE) / 2 - 20);
	// mlx_set_instance_depth(&img->instances[0], 3);
}