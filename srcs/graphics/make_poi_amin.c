/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_poi_amin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 14:27:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/16 14:27:59 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	make_frames(uint8_t **arr, mlx_texture_t *text, int x, int y)
{
	const uint32_t		xy[2] = {48 * x, 48 * y};
	const uint32_t		wh[2] = {48, 48};

	if (y)
		x += 6;
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

uint8_t	**load_poi_anim(t_game *game, mlx_texture_t *txt, int frames, int y)
{
	mlx_texture_t		*text;
	uint8_t				**sprites;
	int					i;
	int					x;

	if (!txt)
		ft_error("so_long", MLX_INVFILE);
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
		{
			x = 0;
			y = 1;
		}
	}
	return (sprites);
}