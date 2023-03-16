/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:48:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/16 12:52:19 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>
#include <MLX42/MLX42_Int.h>

void	update_player(t_player *player)
{
	static int		iter;
	static double	time;
	int				dir;

	if (player->dir == 2)
		dir = 8;
	else
		dir = 0;
	if (mlx_get_time() - time > 0.15)
	{
		player->img->pixels = player->sprites[0][iter % 6 + dir];
		time = mlx_get_time();
		iter++;
	}
}

static void	make_frames(uint8_t **arr, mlx_texture_t *text, int x, int y)
{
	const uint32_t		xy[2] = {48 * x, 48 * y};
	const uint32_t		wh[2] = {48, 48};

	arr[x] = split_text(text, (uint32_t *)xy, (uint32_t *)wh);
	if (!arr[x])
	{
		while (x >= 0)
		{
			free(arr[x]);
			x--;
		}
		free(arr);
		ft_error("so_long", mlx_errno);
	}
}

static uint8_t	**load_player_anim(t_game *game, mlx_texture_t *txt, \
											int frames, int y)
{
	mlx_texture_t		*text;
	uint8_t				**sprites;
	int					i;
	int					x;

	sprites = ft_calloc(frames, sizeof(uint8_t *));
	if (!sprites)
		ft_error("so_long", ENOMEM);
	i = -1;
	x = 0;
	while (++i < frames)
	{
		make_frames(sprites, txt, x, y);
		x++;
		if (i + 1 == frames / 2)
			x = 8;
	}
	return (sprites);
}

void	render_player(t_game *game, t_player *player)
{
	t_pos			*pos;
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	uint8_t			***sprites;

	pos = player->pos;
	img = player->img;
	texture = mlx_load_png("./sprites/player48.png");
	if (!texture)
		ft_error("so_long", mlx_errno);
	sprites = ft_calloc(5, sizeof(uint8_t **));
	if (!sprites)
		ft_error("so_long", ENOMEM);
	sprites[0] = load_player_anim(game, texture, 16, 4);
	sprites[1] = load_player_anim(game, texture, 16, 3);
	sprites[2] = load_player_anim(game, texture, 16, 8);
	sprites[3] = load_player_anim(game, texture, 16, 6);
	sprites[4] = load_player_anim(game, texture, 16, 7);
	player->sprites = sprites;
	img->pixels = player->sprites[0][0];
	mlx_image_to_window(game->mlx, img, \
	SIZE * pos->x + (game->width - game->map_info->cols * SIZE) / 2 - 155, \
	SIZE * pos->y + (game->height - game->map_info->rows * SIZE) / 2 - 20);
	mlx_set_instance_depth(&player->img->instances[0], 3);
}
