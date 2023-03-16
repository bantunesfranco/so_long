/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 11:03:25 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/16 12:00:09 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	clear_collect(t_game *game, t_collect **list)
{
	int			i;
	t_collect	*head;
	t_collect	*temp;

	i = -1;
	head = *list;
	while (head)
	{
		temp = head;
		free(head->pos);
		(*(&head))->img->pixels = NULL;
		mlx_delete_image(game->mlx, head->img);
		(*(&head))->img = NULL;
		head = head->next;
		free(temp);
	}
	free(list);
}

static void	clear_enemies(t_game *game, t_enemy **list)
{
	int		i;
	t_enemy	*head;
	t_enemy	*temp;

	i = -1;
	head = *list;
	while (head)
	{
		temp = head;
		free(head->pos);
		(*(&head))->img->pixels = NULL;
		mlx_delete_image(game->mlx, head->img);
		(*(&head))->img = NULL;
		head = head->next;
		free(temp);
	}
	free(list);
}

static void	clear_player(t_game *game, t_player **player)
{
	int	i;

	i = -1;
	free((*player)->pos);
	free((*player)->start_pos);
	(*player)->img->pixels = NULL;
	mlx_delete_image(game->mlx, (*player)->img);
	(*player)->img = NULL;
	while (++i < 5)
		ft_free_int_arr((int **)(*player)->sprites[i], 16);
	free((*player)->sprites);
	free(*player);
	*player = NULL;
}

void	exit_game(t_game *game)
{
	mlx_close_window(game->mlx);
	clear_spritelist(game, game->map_tiles);
	clear_player(game, &game->player);
	clear_enemies(game, game->enemies);
	clear_collect(game, game->collectibles);
	mlx_terminate(game->mlx);
	exit(EXIT_SUCCESS);
}
