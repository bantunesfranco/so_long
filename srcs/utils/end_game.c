/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end_game.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 12:50:09 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/20 14:34:56 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	end_game(t_game *game)
{
	game->status = LOCKED;
	ft_printf("END");
	exit_game(game);
}
