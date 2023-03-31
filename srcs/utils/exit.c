/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 11:03:25 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/31 13:07:15 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	clear_sprites(t_collect **lst, t_enemy **lst2)
{
	t_collect	*head;
	t_enemy		*head2;

	head = *lst;
	while (head)
	{
		head->img->pixels = NULL;
		head = head->next;
	}
	head2 = *lst2;
	while (head2)
	{
		head2->img->pixels = NULL;
		head2 = head2->next;
	}
}

void	exit_game(t_game *game)
{
	mlx_close_window(game->mlx);
	clear_sprites(game->collectibles, game->enemies);
	mlx_terminate(game->mlx);
	exit(EXIT_SUCCESS);
}
