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

#include "so_long.h"


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
	while (++i < game->enemy_count)
	{

		// Calculate next position
		next_x = game->enemies[i].x;
		next_y = game->enemies[i].y;

		if (game->enemies[i].direction == 'R') next_y++;
		else if (game->enemies[i].direction == 'L') next_y--;
		else if (game->enemies[i].direction == 'D') next_x++;
		else if (game->enemies[i].direction == 'U') next_x--;

		// Check boundaries and walls
		if (next_x < 0 || next_x >= (int)game->height ||
			next_y < 0 || next_y >= (int)game->width ||
			game->map[next_x][next_y] == '1')
		{

			int r = rand() % 4;
			if (r == 0) game->enemies[i].direction = 'R';
			else if (r == 1) game->enemies[i].direction = 'L';
			else if (r == 2) game->enemies[i].direction = 'D';
			else game->enemies[i].direction = 'U';


		}
		else
		{

			game->enemies[i].x = next_x;
			game->enemies[i].y = next_y;
		}
	}
}

/* void	move_enemies(t_map *game)
{
	int	i;
	int	next_x;
	int	next_y;
	int	move_offset;

	i = -1;
	while (++i < game->enemy_count)
	{
		next_x = game->enemies[i].x;
		if (game->enemies[i].direction == 'R')
			move_offset = 1;
		else
			move_offset = -1;
		next_y = game->enemies[i].y + move_offset;

		if (next_y >= 0 && next_y < (int)game->width)
		{
			if (game->map[next_x][next_y] == '1')
			{
				if (game->enemies[i].direction == 'R')
					game->enemies[i].direction = 'L';
				else
					game->enemies[i].direction = 'R';
			}
			else if (game->map[next_x][next_y] != '1')
			{
				game->enemies[i].y = next_y;
			}
		}
		else
		{
			if (game->enemies[i].direction == 'R')
				game->enemies[i].direction = 'L';
			else
				game->enemies[i].direction = 'R';
		}
	}
}
 */
