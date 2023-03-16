/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_poi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:37:21 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/16 12:58:25 by bfranco       ########   odam.nl         */
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

void	update_enemy(t_enemy **list)
{
	static int		iter;
	static double	time;
	int				dir;
	t_enemy			*head;

	head = *list;
	if (mlx_get_time() - time > 0.15)
	{
		while (head)
		{
			if (head->dir == 2)
				dir = 6;
			else
				dir = 0;
			head->img->pixels = head->sprites[iter % 6 + dir];
			head = head->next;
		}
		time = mlx_get_time();
		iter++;
	}
}
