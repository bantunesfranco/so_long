/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_poi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:37:21 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/16 11:13:04 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

uint8_t	**load_poi_anim(t_game *game, mlx_texture_t *txt, \
											int frames, int y)
{
	mlx_texture_t		*text;
	uint8_t			**sprites;
	int					i;
	int					x;

	if (!txt)
		ft_error("so_long", MLX_INVFILE);
	sprites = ft_calloc(frames, sizeof(mlx_texture_t *));
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
			y++;
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