/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:48:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/10 11:05:40 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/so_long.h"
#include "../../MLX42/include/MLX42/MLX42_Int.h"

void	render_player(t_game *game, t_player *player)
{
	t_pos			*pos;
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	pos = player->pos;
	img = player->img;
	texture = mlx_load_png("./sprites/player48.png");
	if (!texture)
		ft_error("so_long", mlx_errno);
	// load_player_anim(game, texture, 6, 4);
	// ft_memmove(img->pixels, player->sprites[0]->pixels, \
	// player->sprites[0]->width * player->sprites[0]->width * BPP);
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	mlx_image_to_window(game->mlx, img, \
	SIZE * pos->x + (game->width - game->map_info->cols * SIZE) / 2 - 155, \
	SIZE * pos->y + (game->height - game->map_info->rows * SIZE) / 2 - 20);
}

void	make_frames(mlx_texture_t **sprites, mlx_texture_t *text, int x, int y)
{
	const uint32_t		xy[2] = {48 * x, 48 * y};
	const uint32_t		wh[2] = {48, 48};

	sprites[x] = mlx_texture_area_to_texture(text, \
	(uint32_t *)xy, (uint32_t *)wh);
}

void	load_player_anim(t_game *game, mlx_texture_t *txt, int frames, int y)
{
	mlx_texture_t		*text;
	mlx_texture_t		**sprites;
	mlx_image_t			*img;
	int					i;
	int					x;

	game->player->sprites = ft_calloc(frames, sizeof(mlx_texture_t *));
	if (!game->player->sprites)
		ft_error("so_long", ENOMEM);
	i = -1;
	x = 0;
	while (++i < frames - 1)
	{
		// ft_printf("%d\n", x);
		make_frames(game->player->sprites, text, x, y);
		x++;
		// if (i == (frames - 1) / 2)
		// 	x = 8;
	}
}
