/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:06:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/04/05 15:13:19 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	render_ui2(t_game *game, t_ui *ui, t_player *player)
{
	char		*str;
	char		*str2;
	const int	width = game->width;
	const int	height = game->height / 2;

	str = ft_itoa(player->lives);
	ui->nb_l = mlx_put_string(game->mlx, str, width - 200, height - 50);
	free(str);
	str = ft_itoa(player->collectibles);
	ui->nb_c = mlx_put_string(game->mlx, str, width - 200, height);
	free(str);
	str = ft_itoa(game->map_info->collectible_count);
	str2 = ft_strjoin("/", str);
	ui->total = mlx_put_string(game->mlx, str2, width - 200 + 11, height);
	free(str);
	free(str2);
	str = ft_itoa(player->moves);
	ui->nb_m = mlx_put_string(game->mlx, str, width - 200, height + 50);
	free(str);
}

void	render_ui(t_game *game, t_ui *ui, t_player *player)
{
	mlx_texture_t	*text;
	const int		width = game->width;
	const int		height = game->height / 2;

	text = mlx_load_png("./sprites/gui.png");
	if (!text)
		ft_error("so_long", mlx_errno);
	ui->background = mlx_texture_to_image(game->mlx, text);
	if (!ui->background)
		ft_error("so_long", mlx_errno);
	mlx_image_to_window(game->mlx, ui->background, \
	width - ui->background->height - PADX / 6, \
	(game->height - ui->background->height) / 2);
	ui->lives = mlx_put_string(game->mlx, "Lives:", width - 400, height - 50);
	ui->col = mlx_put_string(game->mlx, "Collectibles:", width - 400, height);
	ui->moves = mlx_put_string(game->mlx, "Moves:", width - 400, height + 50);
	render_ui2(game, ui, player);
	mlx_delete_texture(text);
}

void	update_ui(t_game *game, t_ui *ui, t_player *player)
{
	char		*str;
	const int	width = game->width;
	const int	height = game->height / 2;

	mlx_delete_image(game->mlx, ui->nb_l);
	mlx_delete_image(game->mlx, ui->nb_c);
	mlx_delete_image(game->mlx, ui->nb_m);
	str = ft_itoa(player->lives);
	ui->nb_l = mlx_put_string(game->mlx, str, width - 200, height - 50);
	free(str);
	str = ft_itoa(player->collectibles);
	ui->nb_c = mlx_put_string(game->mlx, str, width - 200, height);
	free(str);
	str = ft_itoa(player->moves);
	ui->nb_m = mlx_put_string(game->mlx, str, width - 200, height + 50);
	free(str);
}
