/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 14:02:53 by bfranco       #+#    #+#                 */
/*   Updated: 2023/01/16 14:02:53 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <so_long.h>

static bool	check_border(char **map, t_map	*info)
{
	int	i;
	int	len;

	i = -1;
	len = (int)ft_strlen(map[0]);
	while (++i < info->rows)
	{
		if (map[i][0] != '1' || map[i][info->cols - 1] != '1')
			return (false);
		if ((int)ft_strlen(map[i]) != len || (int)ft_strlen(map[i]) < 3)
			return (false);
	}
	i = -1;
	while (++i < info->cols)
	{
		if (map[0][i] != '1' || map[info->rows - 1][i] != '1')
			return (false);
	}
	return (true);
}

static bool	can_collect(char **map, t_map *info)
{
	t_pos		pos;
	int32_t		i;
	int32_t		j;

	i = -1;
	while (++i < info->rows - 1)
	{
		j = -1;
		while (++j < info->rows - 1)
		{
			if (map[i][j] == 'C' || map[i][j] == 'K')
			{
				pos.x = j;
				pos.y = i;
				if (can_exit(map, info, &pos) == false)
					return (false);
			}
		}
	}
	return (true);
}

static bool	get_contents(char **map, t_map *info, t_player *player)
{
	int32_t		i;
	int32_t		j;

	i = -1;
	while (++i < info->rows)
	{
		j = -1;
		while (++j < info->cols)
		{
			if (!ft_strchr("10PECK", map[i][j]))
				return (false);
			if (map[i][j] == 'P')
			{
				info->player_count++;
				player->start_pos->x = j;
				player->start_pos->y = i;
				ft_memcpy(player->pos, player->start_pos, sizeof(t_pos *));
			}
			else if (map[i][j] == 'E')
				info->exit_count++;
			else if (map[i][j] == 'C')
				info->collectible_count++;
		}
	}
	return (true);
}

bool	validate_map(char **map, t_map	*info, t_game *game)
{
	if (check_border(map, info) == false)
		return (false);
	if (get_contents(map, info, game->player) == false)
		return (false);
	if (info->player_count != 1 || info->exit_count != 1)
		return (false);
	if (info->collectible_count == 0)
		return (false);
	if (can_collect(map, info) == false)
		return (false);
	if (can_exit(map, info, game->player->pos) == false)
		return (false);
	return (true);
}
