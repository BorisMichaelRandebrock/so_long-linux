/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@42barcelona.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:04:24 by brandebr          #+#    #+#             */
/*   Updated: 2025/09/17 12:04:28 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include <time.h>
#include <unistd.h>
#include "so_long.h"

unsigned long	get_time_ms(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void	animate_enemies(t_map *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		game->enemies[i].step_count++;
		if (game->enemies[i].step_count >= 3)
		{
			game->enemies[i].frame = (game->enemies[i].frame + 1) % 5;
			game->enemies[i].step_count = 0;
		}
		i++;
	}
}

void	move_enemies(t_map *game)
{
	int	i;
	int	next_x;
	int	next_y;

	i = -1;
	while (++i < (int)game->enemy_count)
	{
		if (rand() % 2 == 0)
			set_random_direction(&game->enemies[i]);
		calculate_next_position(&game->enemies[i], &next_x, &next_y);
		if (next_x < 0 || next_x >= (int)game->height || next_y < 0
			|| next_y >= (int)game->width || game->map[next_x][next_y] == '1')
			set_random_direction(&game->enemies[i]);
		else
		{
			game->enemies[i].x = next_x;
			game->enemies[i].y = next_y;
		}
	}
}

int	enemy_update(void *param)
{
	t_map			*game;
	unsigned long	current_time;

	current_time = get_time_ms();
	game = (t_map *)param;
	game->enemy_frame++;
	if (current_time - game->last_move_time >= 420)
	{
		move_enemies(game);
		ft_enemy_touched(game);
		game->last_move_time = current_time;
	}
	ft_print_map(game);
	draw_enemies(game);
	animate_enemies(game);
	put_movements(game);
	return (0);
}

void	draw_enemies(t_map *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->enemy_img[0][game->enemies[i].frame], game->enemies[i].y
			* SIZE, game->enemies[i].x * SIZE);
		i++;
	}
}
