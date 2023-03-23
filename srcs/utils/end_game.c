/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end_game.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 12:50:09 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/23 12:34:06 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	end_game(t_game *game)
{
	game->status = LOCKED;
	// render game end ui
	if (game->player->status == DEAD)
		ft_printf("YOU LOST :c\n");
	else
		ft_printf("YOU WON :D\n");
	// exit_game(game);
}
