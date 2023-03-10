/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arrays_and_lists.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 09:50:04 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/10 13:19:01 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	enemy_add_back(t_enemy **lst, t_enemy *new)
{
	static t_enemy	*last;

	if (*lst)
	{
		last = *lst;
		last->next = new;
	}
	else
		*lst = new;
}

void	collect_add_back(t_collect **lst, t_collect *new)
{
	static t_collect	*last;

	if (*lst)
	{
		last = *lst;
		last->next = new;
	}
	else
		*lst = new;
}

void	ft_free_int_arr(int **arr, int size)
{
	int	i;

	i = -1;
	if (!arr || size < 1)
		return ;
	while (++i < size)
		free(arr[i]);
	free(arr);
}

void	clear_spritelist(t_game *game, mlx_image_t **arr)
{
	int	i;

	i = 0;
	while (i < game->map_info->size)
	{
		mlx_delete_image(game->mlx, arr[i]);
		i++;
	}
	free(arr);
}
