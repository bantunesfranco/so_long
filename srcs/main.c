/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 13:24:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/10 11:07:12 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

void	update_game(void *param)
{
	t_game	*game;

	game = param;
	// update_player(game, game->player);

	// printf("%d\n", (int32_t)(mlx_get_time() * 100) % 10);

	// update_enemies(game, game->enemies);
	update_player_stats(game, game->player);
}

int	main(int argc, char **argv)
{
	t_game			game;
	mlx_t			*mlx;

	init_game(&game, argv);
	render_map(&game, game.map);
	mlx_loop_hook(game.mlx, update_game, (void *)&game);
	mlx_key_hook(game.mlx, interactions, (void *)&game);
	mlx_loop(game.mlx);
	clear_spritelist(&game, game.map_tiles);
	mlx_terminate(game.mlx);
	exit(EXIT_SUCCESS);
}
