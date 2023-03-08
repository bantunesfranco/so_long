/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:48:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/06 16:01:50 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

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
	// mlx_set_instance_depth(img->instances, 2);
	mlx_delete_texture(texture);
}

void	render_collectibles(t_game *game, int x, int y)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	const uint32_t	xy[2] = {SIZE * 3, SIZE};
	const uint32_t	wh[2] = {SIZE, SIZE};

	texture = mlx_load_png("./sprites/base/TX Props.png");
	img = mlx_texture_area_to_image(game->mlx, texture, \
	(uint32_t *)xy, (uint32_t *)wh);
	mlx_image_to_window(game->mlx, img, \
	SIZE * x + (game->width - game->map_info->cols * SIZE) / 2 - 150, \
	SIZE * y + (game->height - game->map_info->rows * SIZE) / 2);
	// mlx_set_instance_depth(img->instances, 2);
	mlx_delete_texture(texture);
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
	// mlx_set_instance_depth(img->instances, 0);
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
		}
	}
}

void	render_player(t_game *game, t_player *player)
{
	t_pos			*pos;
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	static int		iter;
	const uint32_t	xy[2] = {48 * (iter % 6), 48 * 4};
	const uint32_t	wh[2] = {48, 48};

	texture = mlx_load_png("./sprites/player48.png");
	pos = player->pos;
	if (mlx_get_time() - game->time > 0.13)
	{
		if (img)
			mlx_delete_image(game->mlx, game->player->sprite);
		img = mlx_texture_area_to_image(game->mlx, texture, \
		(uint32_t *)xy, (uint32_t *)wh);
		game->player->sprite = img;
		mlx_image_to_window(game->mlx, img, \
		SIZE * pos->x + (game->width - game->map_info->cols * SIZE) / 2 - 155, \
		SIZE * pos->y + (game->height - game->map_info->rows * SIZE) / 2 - 20);
		game->time = mlx_get_time();
		iter++;
	}
}

mlx_texture_t	*load_spritesheet(mlx_t *mlx, char *file)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(file);
	if (!texture)
		exit(EXIT_FAILURE);
	return (texture);
}
