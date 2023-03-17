/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/19 09:24:44 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/17 11:57:33 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <so_long.h>

static bool	check_file_ext(char *file)
{
	char	*ext;

	ext = ft_strrchr(file, '.');
	if (!ext)
		return (false);
	if (!ft_strncmp(ext, ".ber", 5))
		return (true);
	return (false);
}

static void	init_info(t_map *info)
{
	info->rows = 0;
	info->cols = 0;
	info->size = 0;
	info->player_count = 0;
	info->exit_count = 0;
	info->collectible_count = 0;
	info->visited = NULL;
	info->queue = NULL;
}

static int	get_nb_lines(char *file)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("so_long", errno);
	line = "";
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		lines++;
		free(line);
	}
	if (lines <= 2)
	{
		close(fd);
		ft_printf("Invalid map\n");
		exit(EINVAL);
	}
	return (close(fd), lines);
}

static char	**get_map(char *file, t_map *info)
{
	int		i;
	int		fd;
	char	**map;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("so_long", errno);
	line = "";
	i = -1;
	map = ft_calloc(sizeof(char *), info->rows + 1);
	if (!map)
		ft_error("so_long", ENOMEM);
	while (++i < info->rows)
	{
		line = get_next_line(fd);
		if (!line)
			ft_error("so_long", ENOMEM);
		map[i] = ft_strtrim(line, "\n\0");
		if (!map[i])
			ft_error("so_long", ENOMEM);
		free(line);
	}
	return (close(fd), map);
}

char	**map_parser(char *file, t_game *game)
{
	char	**map;
	t_map	*info;

	if (check_file_ext(file) == false)
	{
		ft_printf("Invalid map\n");
		exit(EINVAL);
	}
	info = malloc(sizeof(t_map));
	if (!info)
		ft_error("so_long", errno);
	init_info(info);
	info->rows = get_nb_lines(file);
	map = get_map(file, info);
	info->cols = (int)ft_strlen(map[0]);
	info->size = info->rows * info->cols;
	game->map_info = info;
	if (validate_map(map, info, game) == false)
	{
		ft_printf("Invalid map\n");
		exit(EINVAL);
	}
	ft_printf("Valid map\n");
	return (map);
}
