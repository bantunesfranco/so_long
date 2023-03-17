/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_poi_amin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 14:27:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/17 12:24:00 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	make_frames(uint8_t **arr, mlx_texture_t *text, int x, int y)
{
	const uint32_t		xy[2] = {SIZE * x, SIZE * y};
	const uint32_t		wh[2] = {SIZE, SIZE * 2};

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

uint8_t	**load_poi_anim(mlx_texture_t *txt, int frames, int y)
{
	uint8_t				**sprites;
	int					i;

	if (!txt)
		ft_error("so_long", MLX_INVFILE);
	sprites = ft_calloc(frames, sizeof(uint8_t *));
	if (!sprites)
		ft_error("so_long", ENOMEM);
	i = -1;
	while (++i < frames)
		make_frames(sprites, txt, i, y);
	return (sprites);
}
