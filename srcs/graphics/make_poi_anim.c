/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_poi_anim.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 14:27:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/28 11:30:18 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	make_frames(uint8_t **arr, mlx_texture_t *text, int x, int y)
{
	const uint32_t		xy[2] = {SIZE * x, SIZE * y};
	const uint32_t		wh[2] = {SIZE, SIZE};

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

static void	make_frames2(uint8_t **arr, mlx_texture_t *text, int x, int y)
{
	const uint32_t		xy[2] = {48 * x + 8, 48 * y};
	const uint32_t		wh[2] = {32, 48};

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

uint8_t	**load_poi_anim(mlx_texture_t *txt, int frames, int y, char type)
{
	uint8_t	**sprites;
	int		i;

	if (!txt)
		ft_error("so_long", MLX_INVFILE);
	sprites = ft_calloc(frames, sizeof(uint8_t *));
	if (!sprites)
		ft_error("so_long", ENOMEM);
	i = -1;
	if (type == 'C')
		while (++i < frames)
			make_frames(sprites, txt, i, y);
	else if (type == 'K')
		while (++i < frames)
			make_frames2(sprites, txt, i, y);
	mlx_delete_texture(txt);
	return (sprites);
}
