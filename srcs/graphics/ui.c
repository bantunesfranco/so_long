/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:06:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/29 13:12:39 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	render_dynamic_ui(t_game *game, t_ui *ui, t_player *player)
{
	char		*str;
	char		*str2;
	const int	width = game->width - 100;
	const int	height = game->height / 2;

	ui = game->ui;
	str = ft_itoa(player->lives);
	ui->nb_l = mlx_put_string(game->mlx, str, width, height - 50);
	free(str);
	str = ft_itoa(player->collectibles);
	ui->nb_c = mlx_put_string(game->mlx, str, width, height);
	free(str);
	str = ft_itoa(game->map_info->collectible_count);
	str2 = ft_strjoin("\\", str);
	str = ft_itoa(player->moves);
	free(str);
	free(str2);
	ui->total = mlx_put_string(game->mlx, str, width + 20, height);
	ui->nb_m = mlx_put_string(game->mlx, str, width, height + 50);
	free(str);
}

void	render_static_ui(t_game *game, t_ui *ui, t_player *player)
{
	char		*str;
	const int	width = game->width - 300;
	const int	height = game->height / 2;

	ui = game->ui;
	ui->lives = mlx_put_string(game->mlx, "Lives:", width, height - 50);
	ui->col = mlx_put_string(game->mlx, "Collectibles:", width, height);
	ui->moves = mlx_put_string(game->mlx, "Moves:", width, height + 50);
	str = ft_itoa(player->lives);
	ui->nb_l = mlx_put_string(game->mlx, str, game->width - 100, height - 50);
	free(str);
	str = ft_itoa(player->collectibles);
	ui->nb_c = mlx_put_string(game->mlx, str, game->width - 100, height);
	free(str);
	str = ft_itoa(player->collectibles);
	ui->nb_m = mlx_put_string(game->mlx, str, game->width - 100, height + 50);
	free(str);
	render_dynamic_ui(game, ui, player);
}


// void	update_ui(t_game *game, t_player *player)
// {
	
// }