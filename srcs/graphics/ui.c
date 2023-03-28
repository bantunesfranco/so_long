/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:06:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/28 14:08:05 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	render_ui(t_game *game, t_player *player)
{
	static int			iter;
	static mlx_image_t	*img;
	static mlx_image_t	*img2;
	static mlx_image_t	*img3;

	if (iter == 0)
	{	
		mlx_put_string(game->mlx, "Lives:", game->width - 300, \
		game->height / 2);
		mlx_put_string(game->mlx, "Collectibles:", \
		game->width - 300, game->height / 2 + 100);
		mlx_put_string(game->mlx, "Moves:", game->width - 300, \
		game->height / 2 + 200);
		img = mlx_put_string(game->mlx, ft_itoa(player->lives), \
		game->width - 100, game->height / 2);
		img2 = mlx_put_string(game->mlx, ft_itoa(player->collectibles), \
		game->width - 100, game->height / 2 + 100);
		img3 = mlx_put_string(game->mlx, ft_itoa(player->collectibles), \
		game->width - 100, game->height / 2 + 200);
		iter = 1;
	}
	if (iter > 0)
	{
		mlx_delete_image(game->mlx, img);
		img = mlx_put_string(game->mlx, ft_itoa(player->lives), \
		game->width - 100, game->height / 2);
		mlx_delete_image(game->mlx, img2);
		img2 = mlx_put_string(game->mlx, ft_itoa(player->collectibles), \
		game->width - 100, game->height / 2 + 100);
		mlx_delete_image(game->mlx, img3);
		img3 = mlx_put_string(game->mlx, ft_itoa(player->moves), \
		game->width - 100, game->height / 2 + 200);
	}
}
