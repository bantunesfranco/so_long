/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end_game.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 12:50:09 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/17 13:03:43 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	end_game(t_game *game)
{
	game->status = INACTIVE;
	ft_printf("END");
	exit_game(game);
}
