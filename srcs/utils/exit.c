/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 11:03:25 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/16 11:18:40 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	clear_player(t_game *game, t_player **player)
{
	int	i;
	int	j;

	free((*player)->pos);
	free((*player)->start_pos);
	(*player)->img->pixels = NULL;
	mlx_delete_image(game->mlx, (*player)->img);
	i = -1;
	while (++i < 5)
	{
		j = -1;
		while (++j < 16)
			free((*player)->sprites[i][j]);
		free((*player)->sprites[i]);
	}
	free((*player)->sprites);
	free(*player);
	*player = NULL;
}

void	exit_game(t_game *game)
{
	mlx_close_window(game->mlx);
	clear_spritelist(game, game->map_tiles);
	clear_player(game, &game->player);
	mlx_terminate(game->mlx);
	exit(EXIT_SUCCESS);
}
