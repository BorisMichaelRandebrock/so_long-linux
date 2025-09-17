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
	int	r;

	i = -1;
	while (++i < game->enemy_count)
	{
		// Calculate next position
		next_x = game->enemies[i].x;
		next_y = game->enemies[i].y;
		if (game->enemies[i].direction == 'R')
			next_y++;
		else if (game->enemies[i].direction == 'L')
			next_y--;
		else if (game->enemies[i].direction == 'D')
			next_x++;
		else if (game->enemies[i].direction == 'U')
			next_x--;
		// Check boundaries and walls
		if (next_x < 0 || next_x >= (int)game->height || next_y < 0
			|| next_y >= (int)game->width || game->map[next_x][next_y] == '1')
		{
			r = rand() % 4;
			if (r == 0)
				game->enemies[i].direction = 'R';
			else if (r == 1)
				game->enemies[i].direction = 'L';
			else if (r == 2)
				game->enemies[i].direction = 'D';
			else
				game->enemies[i].direction = 'U';
		}
		else
		{
			game->enemies[i].x = next_x;
			game->enemies[i].y = next_y;
		}
	}
}

int	enemy_update(void *param)
{
	t_map	*game;

	game = (t_map *)param;
	game->enemy_frame++;
	if (game->enemy_frame % 99 == 0)
	{
		move_enemies(game);
		ft_enemy_touched(game); // ← Make sure this exists too
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
/*
void	parse_enemies(t_map *game)
{
	int	count;

	count = 0, i;
	while (++i < (int)game->height)
	{
		j = -1;
		while (++j < (int)game->width)
			if (game->map[i][j] == 'B')
				count++;
	}
	if (count > 0)
	{
		game->enemies = malloc(sizeof(t_enemy) * count);
		if (!game->enemies)
			exit_error(game, "Error\nFailed to allocate enemies\n", 0);
		game->enemy_count = count;
		i = -1;
		while (++i < (int)game->height)
		{
			j = -1;
			while (++j < (int)game->width)
			{
				if (game->map[i][j] == 'B')
				{
					game->enemies[idx].x = i;
					game->enemies[idx].y = j;
					game->enemies[idx].chaos = rand() % 10 + 1;
					game->enemies[idx].frame = 0;
					game->enemies[idx].step_count = 0;
					game->enemies[idx].direction = 'R';
					game->map[i][j] = '0';
					idx++;
				}
			}
		}
	}
	else
	{
		game->enemies = NULL;
		game->enemy_count = 0;
	}
}

 */

void	parse_enemies(t_map *game)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	int j;       // ← DECLARE j
	int idx = 0; // ← DECLARE idx
	while (++i < (int)game->height)
	{
		j = -1;
		while (++j < (int)game->width)
			if (game->map[i][j] == 'B')
				count++;
	}
	if (count > 0)
	{
		game->enemies = malloc(sizeof(t_enemy) * count);
		if (!game->enemies)
			exit_error(game, "Error\nFailed to allocate enemies\n", 0);
		game->enemy_count = count;
		i = -1;
		while (++i < (int)game->height)
		{
			j = -1;
			while (++j < (int)game->width)
			{
				if (game->map[i][j] == 'B')
				{
					game->enemies[idx].x = i;
					game->enemies[idx].y = j;
					game->enemies[idx].chaos = rand() % 10 + 1;
					game->enemies[idx].frame = 0;
					game->enemies[idx].step_count = 0;
					game->enemies[idx].direction = 'R';
					game->map[i][j] = '0';
					idx++;
				}
			}
		}
	}
	else
	{
		game->enemies = NULL;
		game->enemy_count = 0;
	}
}

void	ft_upload_enemies(t_map *game, int height, int width)
{
	char	*frame_paths[5] = {"imgs/Enemy/Anim/Bat_0.xpm",
			"imgs/Enemy/Anim/Bat_1.xpm", "imgs/Enemy/Anim/Bat_2.xpm",
			"imgs/Enemy/Anim/Bat_3.xpm", "imgs/Enemy/Anim/Bat_4.xpm"};

	for (int frame = 0; frame < 5; frame++)
	{
		game->enemy_img[0][frame] = mlx_xpm_file_to_image(game->mlx_ptr,
				frame_paths[frame], &width, &height);
		if (!game->enemy_img[0][frame])
			exit_error(game, "Error\nFailed to load enemy animation frame\n",
				0);
	}
}
/* void	parse_enemies(t_map *game)
{
	int	count;

	count = 0, i;
	// count = 0, i = -1, j, idx;
	count = 0, i = -1, j = 0, idx = 0;
	while (++i < (int)game->height)
	{
		j = -1;
		while (++j < (int)game->width)
			if (game->map[i][j] == 'B')
				count++;
	}
	if (count > 0)
	{
		if (!(game->enemies = malloc(sizeof(t_enemy) * count)))
			exit_error(game, "Error\nFailed to allocate enemies\n", 0);
		game->enemy_count = count;
		i = -1;
		while (++i < (int)game->height && count > 0)
		{
			j = -1;
			while (++j < (int)game->width)
			{
				if (game->map[i][j] == 'B')
				{
					game->enemies[idx].x = i;
					game->enemies[idx].y = j;
					game->enemies[idx].chaos = rand() % 10 + 1;
					game->enemies[idx].frame = 0;
					game->enemies[idx].step_count = 0;
					game->enemies[idx].direction = 'R';
					game->map[i][j] = '0';
					idx++;
				}
			}
		}
	}
	// if (count == 0) { game->enemies = NULL; game->enemy_count = 0; }
} */
