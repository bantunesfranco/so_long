/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_walls.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 15:44:31 by bfranco       #+#    #+#                 */
/*   Updated: 2023/04/05 15:07:43 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	render_middle(t_game *game, mlx_texture_t *texture, int x, int y)
{
	mlx_image_t		*img;
	const uint32_t	xy[2] = {SIZE * 11, SIZE};
	const uint32_t	wh[2] = {SIZE, SIZE};

	img = mlx_texture_area_to_image(game->mlx, texture, \
	(uint32_t *)xy, (uint32_t *)wh);
	mlx_image_to_window(game->mlx, img, \
	SIZE * x + PADX / 8, SIZE * y + PADY / 2);
	mlx_set_instance_depth(img->instances, 1);
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
		SIZE * x + PADX / 8, SIZE * (y - 1) + PADY / 2);
	}
	else
	{
		img = mlx_texture_area_to_image(game->mlx, texture, \
		(uint32_t *)xy2, (uint32_t *)wh);
		mlx_image_to_window(game->mlx, img, \
		SIZE * x + PADX / 8, SIZE * y + PADY / 2);
	}
	mlx_set_instance_depth(img->instances, 1);
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
		SIZE * x + PADX / 8, SIZE * y + PADY / 2);
	}
	else
	{
		img = mlx_texture_area_to_image(game->mlx, texture, \
		(uint32_t *)xy, (uint32_t *)wh);
		mlx_image_to_window(game->mlx, img, \
		SIZE * x + PADX / 8, SIZE * y + PADY / 2);
	}
	mlx_set_instance_depth(img->instances, 1);
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
		SIZE * x + PADX / 8, SIZE * (y - 1) + PADY / 2);
	}
	else
	{
		img = mlx_texture_area_to_image(game->mlx, texture, \
		(uint32_t *)xy, (uint32_t *)wh);
		mlx_image_to_window(game->mlx, img, \
		SIZE * x + PADX / 8, SIZE * y + PADY / 2);
	}
	mlx_set_instance_depth(img->instances, 1);
}

void	render_walls(t_game *game, int x, int y)
{
	mlx_texture_t	*spritesheet;

	spritesheet = mlx_load_png("./sprites/wall.png");
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
		render_middle(game, spritesheet, x, y);
	mlx_delete_texture(spritesheet);
}
