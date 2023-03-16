/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   play_anim.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 11:21:58 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/16 11:18:03 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	play_anim(t_player *player, uint8_t **arr, int frames)
{
	int		i;
	int		dir;
	double	time;

	i = 0;
	if (player->dir == LEFT)
		dir = 8;
	else
		dir = 0;
	time = mlx_get_time();
	while (true)
	{
		if (mlx_get_time() - time > 0.1)
		{
			player->img->pixels = arr[i + dir];
			time = mlx_get_time();
			i++;
		}
		if (i == frames)
			break ;
	}
}
