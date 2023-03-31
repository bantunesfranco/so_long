/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 13:24:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/31 16:36:39 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

float	delay(t_player *player)
{
	if (player->status == ATK)
		return (0.025);
	if (player->status == WALK)
		return (0.05);
	if (player->status == DMG)
		return (0.15);
	if (player->status == DEAD)
		return (0.05);
	return (0);
}

void	update_game(void *param)
{
	t_game			*game;
	t_pos			*pos;
	static double	time;

	game = param;
	pos = game->player->pos;
	update_enemy(game->enemies);
	update_collectible(game->collectibles);
	if (game->status == UNLOCKED)
	{
		update_player(game->player);
		collect(game, game->collectibles, game->player->pos);
	}
	else if (mlx_get_time() - time > delay(game->player) \
	&& game->status == LOCKED)
	{
		update_anim(game, game->player);
		time = mlx_get_time();
	}
	update_player_stats(game, game->player);
}

// void	leaks(void)
// {
// 	system("leaks -q  so_long");
// }

int	main(int argc, char **argv)
{
	t_game			game;

	// atexit(leaks);
	if (argc != 2)
	{
		ft_putendl_fd(ARG, 2);
		exit(EXIT_FAILURE);
	}
	ft_printf("%s\n", CMDS);
	init_game(&game, argv);
	render_map(&game, game.map);
	render_ui(&game, game.ui, game.player);
	mlx_loop_hook(game.mlx, update_game, &game);
	mlx_key_hook(game.mlx, interactions, &game);
	mlx_loop(game.mlx);
	exit_game(&game);
}
