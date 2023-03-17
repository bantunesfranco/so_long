/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:06:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/17 15:26:18 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	render_ui(t_game *game, t_player *player)
{
	static int	iter;
	mlx_image_t	*img;
	mlx_image_t	*img2;

	img = mlx_put_string(game->mlx, ft_itoa(player->lives), game->width - 100, game->height/2);
	if (img && iter != 0)
		mlx_delete_image(game->mlx, img);
	img2 = mlx_put_string(game->mlx, ft_itoa(player->collectibles), game->width - 50, game->height/2 + 50);
	if (img2 && iter != 0)
		mlx_delete_image(game->mlx, img2);
	if (!iter)
	{
		mlx_put_string(game->mlx, "Lives:", game->width - 200, game->height/2);
		mlx_put_string(game->mlx, "Collectibles:", game->width - 200, game->height/2 + 50);
		iter = 1;
	}
}
