/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_poi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:37:21 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/30 12:54:01 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	move_enemy(t_enemy *enemy, int *i)
{
	const t_dir	mvs[4] = {UP, DOWN, LEFT, RIGHT};

	if (!*i)
		enemy->move_dir = mvs[0];
	ft_printf("%d\n", enemy->move_dir);
	// move_sprite((t_player *)enemy, enemy->move_dir);
	*i += 1;
	if (*i == 8)
		*i = 0;
	if (enemy->move_dir == UP && !*i)
		enemy->pos->y -= 1;
	if (enemy->move_dir == DOWN && !*i)
		enemy->pos->y += 1;
	if (enemy->move_dir == LEFT && !*i)
		enemy->pos->x -= 1;
	if (enemy->move_dir == RIGHT && !*i)
		enemy->pos->x += 1;
}

void	update_enemy(t_enemy **list)
{
	static int		i = 0;
	static int		iter = 0;
	static double	time = 0;
	int				dir;
	t_enemy			*head;

	head = *list;
	if (mlx_get_time() - time > 0.15)
	{
		while (head)
		{
			if (head->dir == LEFT)
				dir = 6;
			else
				dir = 0;
			move_enemy(head, &i);
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
