/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:06:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/17 17:00:17 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	render_ui(t_game *game, t_player *player)
{
	static int			iter;
	static mlx_image_t	*img;
	static mlx_image_t	*img2;

	if (iter == 0)
	{	
		img = mlx_put_string(game->mlx, ft_itoa(player->lives), game->width - 100, game->height/2);
		img2 = mlx_put_string(game->mlx, ft_itoa(player->collectibles), game->width - 100, game->height/2 + 35);
	}
	if (iter >= 0)
	{
		// mlx_delete_image(game->mlx, img);
		img = mlx_put_string(game->mlx, ft_itoa(player->lives), game->width - 100, game->height/2);
		mlx_delete_image(game->mlx, img2);
		img2 = mlx_put_string(game->mlx, ft_itoa(player->collectibles), game->width - 100, game->height/2 + 35);
	}
	if (!iter)
	{
		mlx_put_string(game->mlx, "Lives:", game->width - 300, game->height/2);
		mlx_put_string(game->mlx, "Collectibles:", game->width - 300, game->height/2 + 35);
		iter = 1;
	}
}
