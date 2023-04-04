/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end_game.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 12:50:09 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/31 17:05:45 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	end_screen(t_game *game, t_ui *ui, char *str)
{
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
	game->width / 2 - 90, game->height / 2 - 25);
}

void	end_game(t_game *game)
{

	if (game->player->status == DEAD)
		ft_printf("You Lost!!\n");
	else
		ft_printf("You Won!!\n");
	exit_game(game);
}
