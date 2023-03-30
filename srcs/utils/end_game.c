/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end_game.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 12:50:09 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/30 12:16:16 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	end_screen(t_game *game, t_ui *ui, char *str)
{
	const double	time = mlx_get_time();
	mlx_texture_t	*text;

	text = mlx_load_png("./sprites/end_bg.png");
	if (!text)
		ft_error("so_long", mlx_errno);
	ui->end = mlx_texture_to_image(game->mlx, text);
	if (!ui->end)
		ft_error("so_long", mlx_errno);
	mlx_image_to_window(game->mlx, ui->end, \
	game->width / 2 - 150, game->height / 2 - 50);
	ui->end_msg = mlx_put_string(game->mlx, str, \
	game->width / 2 - 100, game->height / 2 - 25);
	if (game->status == RESTART)
	{
		while (true)
		{
			if (mlx_get_time() - time > 2.00)
				break ;
		}
		mlx_delete_image(game->mlx, ui->end_msg);
		mlx_delete_image(game->mlx, ui->end);
	}
}

void	end_game(t_game *game)
{
	const double	time = mlx_get_time();

	game->status = LOCKED;
	if (game->player->status == DEAD)
		end_screen(game, game->ui, "YOU LOST");
	else
		end_screen(game, game->ui, "YOU WON");
	while (1)
	{
		if (mlx_get_time() - time > 5.0)
			break ;
	}
	exit_game(game);
}
