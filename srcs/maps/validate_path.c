/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/19 09:38:55 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/31 16:36:13 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <so_long.h>

static bool	is_valid_coord(t_pos *new, t_map *info, char **map)
{
	int32_t	x;
	int32_t	y;

	x = new->x;
	y = new->y;
	if (!(x >= 1 && x < info->cols - 1 && y >= 1 && y < info->rows - 1))
		return (false);
	if (!(!info->visited[y][x] && (map[y][x] == 'E' || map[y][x] == 'C' \
	|| map[y][x] == '0' || map[y][x] == 'P' || map[y][x] == 'K')))
		return (false);
	return (true);
}

static int	**alloc_visited(t_map *info)
{
	int32_t	**visited;
	int32_t	i;

	visited = ft_calloc(info->rows, sizeof(int32_t *));
	if (!visited)
		return (NULL);
	i = -1;
	while (++i < info->rows)
	{
		visited[i] = ft_calloc(info->cols, sizeof(int32_t));
		if (!visited[i])
			return (ft_free_int_arr(visited, i), NULL);
	}
	return (visited);
}

static bool	look_around(char **map, t_map *info, t_pos *curr, int *rear)
{
	t_pos		new;
	int32_t		i;
	const int	dir[2][4] = {{0, 1, 0, -1}, {-1, 0, 1, 0}};

	i = -1;
	while (++i < 4)
	{
		new.y = curr->y + dir[0][i];
		new.x = curr->x + dir[1][i];
		if (is_valid_coord(&new, info, map))
		{
			info->queue[*rear].x = new.x;
			info->queue[*rear].y = new.y;
			*rear += 1;
			info->visited[new.y][new.x] = true;
		}
	}
	return (true);
}

static bool	dequeue(char **map, t_map *info, int front, int rear)
{
	t_pos	curr;

	while (front != rear)
	{
		curr = info->queue[front];
		front++;
		if (map[curr.y][curr.x] == 'E')
		{
			free(info->queue);
			ft_free_int_arr(info->visited, info->rows);
			return (true);
		}
		if (look_around(map, info, &curr, &rear) == false)
		{
			free(info->queue);
			ft_free_int_arr(info->visited, info->rows);
			return (false);
		}
	}
	free(info->queue);
	ft_free_int_arr(info->visited, info->rows);
	return (false);
}

bool	can_exit(char **map, t_map *info, t_pos *pos)
{
	int32_t		front;
	int32_t		rear;

	front = 0;
	rear = 0;
	info->queue = (t_pos *)ft_calloc(info->size, sizeof(t_pos));
	if (!info->queue)
		ft_error("so_long", ENOMEM);
	info->visited = alloc_visited(info);
	if (!info->visited)
		ft_error("so_long", ENOMEM);
	ft_bzero(info->visited, sizeof(info->visited));
	info->queue[rear].x = pos->x;
	info->queue[rear].y = pos->y;
	rear++;
	info->visited[pos->y][pos->x] = true;
	if (dequeue(map, info, front, rear) == false)
		return (false);
	return (true);
}
