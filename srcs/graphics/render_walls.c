/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_walls.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 15:44:31 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/06 13:18:24 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

static void	render_middle(t_game *game, mlx_texture_t *texture, int x, int y)
{
	mlx_image_t		*img;
	const uint32_t	xy[2] = {SIZE * 9, SIZE * 8};
	const uint32_t	wh[2] = {SIZE, SIZE};

	img = mlx_texture_area_to_image(game->mlx, texture, \
	(uint32_t *)xy, (uint32_t *)wh);
	mlx_image_to_window(game->mlx, img, \
	SIZE * x + (game->width - game->map_info->cols * SIZE) / 2 - 150, \
	SIZE * y + (game->height - game->map_info->rows * SIZE) / 2);
	// mlx_set_instance_depth(img->instances, 1);
	game->map_tiles[x + game->map_info->cols * y] = img;
}

static void	render_corners(t_game *game, mlx_texture_t *texture, int x, int y)
{
	mlx_image_t		*img;
	const uint32_t	xy[2] = {SIZE * (7 + (x != 0) % 2), 0};
	const uint32_t	xy2[2] = {SIZE * (5 + (x != 0) % 2), 0};
	const uint32_t	wh[2] = {SIZE, 64};

	if (y == 0)
	{	
		img = mlx_texture_area_to_image(game->mlx, texture, \
		(uint32_t *)xy, (uint32_t *)wh);
		mlx_image_to_window(game->mlx, img, \
		SIZE * x + (game->width - game->map_info->cols * SIZE) / 2 - 150, \
		SIZE * (y - 1) + (game->height - game->map_info->rows * SIZE) / 2);
	}
	else
	{
		img = mlx_texture_area_to_image(game->mlx, texture, \
		(uint32_t *)xy2, (uint32_t *)wh);
		mlx_image_to_window(game->mlx, img, \
		SIZE * x + (game->width - game->map_info->cols * SIZE) / 2 - 150, \
		SIZE * y + (game->height - game->map_info->rows * SIZE) / 2);
	}
	// mlx_set_instance_depth(img->instances, 1);
	game->map_tiles[x + game->map_info->cols * y] = img;
}

static void	render_leftright(t_game *game, mlx_texture_t *texture, int x, int y)
{
	mlx_image_t		*img;
	const uint32_t	xy[2] = {SIZE * (9 + (x != 0) % 2), 0};
	const uint32_t	wh[2] = {SIZE, SIZE};

	if (x == 0)
	{	
		img = mlx_texture_area_to_image(game->mlx, texture, \
		(uint32_t *)xy, (uint32_t *)wh);
		mlx_image_to_window(game->mlx, img, \
		SIZE * x + (game->width - game->map_info->cols * SIZE) / 2 - 150, \
		SIZE * y + (game->height - game->map_info->rows * SIZE) / 2);
	}
	else
	{
		img = mlx_texture_area_to_image(game->mlx, texture, \
		(uint32_t *)xy, (uint32_t *)wh);
		mlx_image_to_window(game->mlx, img, \
		SIZE * x + (game->width - game->map_info->cols * SIZE) / 2 - 150, \
		SIZE * y + (game->height - game->map_info->rows * SIZE) / 2);
	}
	// mlx_set_instance_depth(img->instances, 1);
	game->map_tiles[x + game->map_info->cols * y] = img;
}

static void	render_topbot(t_game *game, mlx_texture_t *texture, int x, int y)
{
	mlx_image_t		*img;
	const uint32_t	xy[2] = {SIZE * (rand() % 5), 0};
	const uint32_t	wh[2] = {SIZE, 64};

	if (y == 0)
	{	
		img = mlx_texture_area_to_image(game->mlx, texture, \
		(uint32_t *)xy, (uint32_t *)wh);
		mlx_image_to_window(game->mlx, img, \
		SIZE * x + (game->width - game->map_info->cols * SIZE) / 2 - 150, \
		SIZE * (y - 1) + (game->height - game->map_info->rows * SIZE) / 2);
	}
	else
	{
		img = mlx_texture_area_to_image(game->mlx, texture, \
		(uint32_t *)xy, (uint32_t *)wh);
		mlx_image_to_window(game->mlx, img, \
		SIZE * x + (game->width - game->map_info->cols * SIZE) / 2 - 150, \
		SIZE * y + (game->height - game->map_info->rows * SIZE) / 2);
	}
	// mlx_set_instance_depth(img->instances, 1);
	game->map_tiles[x + game->map_info->cols * y] = img;
}

void	render_walls(t_game *game, int x, int y)
{
	mlx_texture_t	*spritesheet;
	mlx_texture_t	*spritesheet2;

	spritesheet = mlx_load_png("./sprites/wall.png");
	spritesheet2 = mlx_load_png("./sprites/base/TX Props.png");
	if (x > 0 && x < game->map_info->cols - 1 \
	&& (y == 0 || y == game->map_info->rows - 1))
		render_topbot(game, spritesheet, x, y);
	else if ((x == 0 || x == game->map_info->cols - 1) \
	&& (y > 0 && y < game->map_info->rows - 1))
		render_leftright(game, spritesheet, x, y);
	else if ((x == 0 || x == game->map_info->cols - 1) \
	&& (y == 0 || y == game->map_info->rows - 1))
		render_corners(game, spritesheet, x, y);
	else
		render_middle(game, spritesheet2, x, y);
	mlx_delete_texture(spritesheet);
	mlx_delete_texture(spritesheet2);
}
