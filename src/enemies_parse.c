/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@42barcelona.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:25:57 by brandebr          #+#    #+#             */
/*   Updated: 2025/09/18 12:26:01 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_enemies(t_map *game)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = -1;
	while (++i < (int)game->height)
	{
		j = -1;
		while (++j < (int)game->width)
		{
			if (game->map[i][j] == 'B')
				count++;
		}
	}
	return (count);
}

static void	init_single_enemy(t_enemy *enemy, int x, int y)
{
	enemy->x = x;
	enemy->y = y;
	enemy->chaos = rand() % 10 + 1;
	enemy->frame = 0;
	enemy->step_count = 0;
	enemy->direction = 'R';
}

static void	initialize_enemies(t_map *game, int count)
{
	int	i;
	int	j;
	int	idx;

	game->enemies = malloc(sizeof(t_enemy) * count);
	if (!game->enemies)
		exit_error(game, "Error\nFailed to allocate enemies\n", 0);
	game->enemy_count = count;
	idx = 0;
	i = -1;
	while (++i < (int)game->height)
	{
		j = -1;
		while (++j < (int)game->width)
		{
			if (game->map[i][j] == 'B')
			{
				init_single_enemy(&game->enemies[idx], i, j);
				game->map[i][j] = '0';
				idx++;
			}
		}
	}
}

void	parse_enemies(t_map *game)
{
	int	count;

	count = count_enemies(game);
	if (count > 0)
		initialize_enemies(game, count);
	else
	{
		game->enemies = NULL;
		game->enemy_count = 0;
	}
}

int	is_valid_number(char *str, int *level)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	*level = 0;
	i = 0;
	while (str[i])
	{
		*level = *level * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}
