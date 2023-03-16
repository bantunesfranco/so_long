/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 15:04:27 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/16 11:13:22 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	render_exit(t_game *game, int x, int y)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	const uint32_t	xy[2] = {SIZE * 11, 0};
	const uint32_t	wh[2] = {SIZE, SIZE};

	texture = mlx_load_png("./sprites/wall.png");
	img = mlx_texture_area_to_image(game->mlx, texture, \
	(uint32_t *)xy, (uint32_t *)wh);
	mlx_image_to_window(game->mlx, img, \
	SIZE * x + (game->width - game->map_info->cols * SIZE) / 2 - 150, \
	SIZE * y + (game->height - game->map_info->rows * SIZE) / 2 + 5);
	mlx_set_instance_depth(&img->instances[0], 2);
}

void	render_enemies(t_game *game, int x, int y)
{
	t_enemy			*head;
	const uint32_t	xy[2] = {0, 0};
	const uint32_t	wh[2] = {48, 48};

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

void	render_collectibles(t_game *game, int x, int y)
{
	t_collect		*head;
	const uint32_t	xy[2] = {SIZE * 3, SIZE};
	const uint32_t	wh[2] = {SIZE, SIZE};

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
	SIZE * y + (game->height - game->map_info->rows * SIZE) / 2 - 20);
	// mlx_set_instance_depth(&img->instances[0], 3);
}

void	render_floor(t_game *game, int x, int y)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	const uint32_t	xy[2] = {SIZE * (rand() % 6), SIZE * (rand() % 8)};
	const uint32_t	wh[2] = {SIZE, SIZE};

	texture = mlx_load_png("./sprites/base/TX Tileset Grass.png");
	img = mlx_texture_area_to_image(game->mlx, texture, \
	(uint32_t *)xy, (uint32_t *)wh);
	mlx_image_to_window(game->mlx, img, \
	SIZE * x + (game->width - game->map_info->cols * SIZE) / 2 - 150, \
	SIZE * y + (game->height - game->map_info->rows * SIZE) / 2 + 5);
	mlx_set_instance_depth(&img->instances[0], 1);
	mlx_delete_texture(texture);
}

void	render_map(t_game *game, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map_info->rows)
	{
		j = -1;
		while (++j < game->map_info->cols)
		{
			if (i < game->map_info->rows - 1)
				render_floor(game, j, i);
			if (map[i][j] == '1')
				render_walls(game, j, i);
			else if (map[i][j] == 'C')
				render_collectibles(game, j, i);
			else if (map[i][j] == 'E')
				render_exit(game, j, i);
			else if (map[i][j] == 'K')
				render_enemies(game, j, i);
			else if (map[i][j] == 'P')
				render_player(game, game->player);
		}
	}
}
