/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 13:24:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/17 13:08:34 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	update_game(void *param)
{
	t_game	*game;
	t_pos	*pos;

	game = param;
	pos = game->player->pos;
	update_enemy(game->enemies);
	update_player(game->player);
	update_player_stats(game, game->player);
	if ((game->player->status == CAN_EXIT && game->map[pos->y][pos->x] == 'E') \
	|| game->player->status == DEAD)
		end_game(game);
}

int	main(int argc, char **argv)
{
	t_game			game;

	if (argc != 2)
	{
		ft_putendl_fd("Incorrect number of arguments", 2);
		exit(22);
	}
	init_game(&game, argv);
	render_map(&game, game.map);
	mlx_loop_hook(game.mlx, update_game, (void *)&game);
	mlx_key_hook(game.mlx, interactions, (void *)&game);
	mlx_loop(game.mlx);
	exit_game(&game);
}
