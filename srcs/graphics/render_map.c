/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 15:04:27 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/28 17:52:40 by bfranco       ########   odam.nl         */
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
	SIZE * x + PADX / 8, SIZE * y + PADY / 2);
	mlx_set_instance_depth(&img->instances[0], 1);
}

void	render_floor(t_game *game, int x, int y)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	const uint32_t	xy[2] = {SIZE * (rand() % 6), SIZE * (rand() % 8)};
	const uint32_t	wh[2] = {SIZE, SIZE};

	texture = mlx_load_png("./sprites/grass.png");
	img = mlx_texture_area_to_image(game->mlx, texture, \
	(uint32_t *)xy, (uint32_t *)wh);
	mlx_image_to_window(game->mlx, img, \
	SIZE * x + PADX / 8, SIZE * y + PADY / 2);
	mlx_set_instance_depth(&img->instances[0], 0);
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
