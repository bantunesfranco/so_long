#include "Libft/libft.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct s_pos
{
	int x;
	int y;
}		t_pos;

typedef struct s_player
{
	t_pos	*pos;
	int		lives;
}		t_player;

typedef struct s_game
{
	int			rows;
	int			cols;
	t_list		**enemies;
	t_list		**collectibles;
	t_player	*player;
}		t_game;

typedef struct s_enemy
{
	t_pos	*pos;
	bool	killed;
}		t_enemy;

typedef struct s_collect
{
	t_pos	*pos;
	bool	collected;
}		t_collect;

void add_collect(t_list **list, int x, int y)
{
	static t_list	*last;
	t_list			*new;
	t_collect		*collect;

	collect = ft_calloc(1, sizeof(t_collect));
	// if (!collect)
	// 	ft_error("so_long", ENOMEM);
	collect->pos = ft_calloc(1, sizeof(t_pos));
	// if (!collect->pos)
	// 	ft_error("so_long", ENOMEM);
	collect->pos->x = x;
	collect->pos->y = y;
	collect->collected = false;
	new = ft_lstnew(collect);
	// if (!new)
	// 	ft_error("so_long", ENOMEM);
	if (!*list)
		ft_lstadd_back(list, new);
	else
		ft_lstadd_back(&last, new);
	last = new;
}

void add_enemy(t_list **list, int x, int y)
{
	static t_list	*last;
	t_list			*new;
	t_enemy			*enemy;
	static int		i = 0;

	enemy = ft_calloc(1, sizeof(t_enemy));
	// if (!enemy)
	// 	ft_error("so_long", ENOMEM);
	enemy->pos = ft_calloc(1, sizeof(t_pos));
	// if (!enemy->pos)
	// 	ft_error("so_long", ENOMEM);
	enemy->pos->x = x;
	enemy->pos->y = y;
	if (i % 2 == 0)
		enemy->killed = false;
	else
		enemy->killed = true;
	new = ft_lstnew(enemy);
	// if (!new)
	// 	ft_error("so_long", ENOMEM);
	if (!*list)
		ft_lstadd_back(list, new);
	else
		ft_lstadd_back(&last, new);
	last = new;
	i++;
}

void	func(t_game *game, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->rows)
	{
		j = -1;
		while (++j < game->cols)
		{
			printf("%c", map[i][j]);
			if (map[i][j] == 'C')
				add_collect(game->collectibles, j, i);
			if (map[i][j] == 'K')
				add_enemy(game->enemies, j, i);
			if (map[i][j] == 'P')
			{
				game->player->pos->x = j;
				game->player->pos->y = i;
			}
		}
		printf("\n");
	}
}


void	take_damage(t_player *player, t_list **list)
{
	t_list	*head;
	t_enemy	*enemy;

	head = *list;
	while (head)
	{
		enemy = head->content;
		if (player->pos->x == enemy->pos->x && player->pos->y == enemy->pos->y)
		{
			player->lives -= 1;
			printf("DAMAGE!!! %d\n", player->lives);
			break ;
		}
		head = head->next;
	}
}

int main(void)
{
	t_game		game;
	char		*str = "111111 1PKKK1 1KKKK1 10EKK1 10CKK1 111111";
	char		**map;

	map = ft_split(str, ' ');
	game.rows = 6;
	game.cols = 6;
	game.enemies = malloc(sizeof(t_list*));
	game.collectibles = malloc(sizeof(t_list*));
	game.player = malloc(sizeof(t_player*));
	game.player->pos = ft_calloc(1, sizeof(t_pos*));
	game.player->lives = 3;
	func(&game, map);
	while (game.player->lives)
	{
		game.player->pos->x += 1;
		printf("(%d, %d) ", game.player->pos->x, game.player->pos->y);
		take_damage(game.player, game.enemies);
		if (game.player->lives == 0)
			printf("dead!!\n");
		game.player->pos->y += 1;
	}
	printf("END!!!!!");
}