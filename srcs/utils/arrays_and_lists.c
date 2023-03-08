/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arrays_and_lists.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 09:50:04 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/06 16:43:30 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

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
