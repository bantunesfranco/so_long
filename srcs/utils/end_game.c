/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end_game.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 12:50:09 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/28 14:01:37 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	end_game(t_game *game)
{
	const double	time = mlx_get_time();

	game->status = LOCKED;
	if (game->player->status == DEAD)
	{
		ft_printf("YOU LOST :c\n");
	}
	else
		ft_printf("YOU WON :D\n");
	while (1)
	{
		if (mlx_get_time() - time > 5.0)
			break ;
	}
	exit_game(game);
}
