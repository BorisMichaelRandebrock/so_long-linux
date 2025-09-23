/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@42barcelona.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:19:10 by brandebr          #+#    #+#             */
/*   Updated: 2025/09/17 17:19:14 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_movements(t_map *game)
{
	char	buffer[32];

	snprintf(buffer, sizeof(buffer), "Movements: %d", game->count);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 15, 15, 0xFFFFFF, buffer);
}

void	ft_upload_enemies(t_map *game, int height, int width)
{
	int		frame;
	char	*frame_paths[5];

	frame_paths[0] = "imgs/Enemy/Anim/Bat_0.xpm";
	frame_paths[1] = "imgs/Enemy/Anim/Bat_1.xpm";
	frame_paths[2] = "imgs/Enemy/Anim/Bat_2.xpm";
	frame_paths[3] = "imgs/Enemy/Anim/Bat_3.xpm";
	frame_paths[4] = "imgs/Enemy/Anim/Bat_4.xpm";
	frame = 0;
	while (frame < 5)
	{
		game->enemy_img[0][frame] = mlx_xpm_file_to_image(game->mlx_ptr,
				frame_paths[frame], &width, &height);
		if (!game->enemy_img[0][frame])
			exit_error(game, "Error\nFailed to load enemy animation frame\n",
				0);
		frame++;
	}
}

void	set_random_direction(t_enemy *enemy)
{
	int	r;

	r = rand() % 4;
	if (r == 0)
		enemy->direction = 'R';
	else if (r == 1)
		enemy->direction = 'L';
	else if (r == 2)
		enemy->direction = 'D';
	else
		enemy->direction = 'U';
}

void	calculate_next_position(t_enemy *enemy, int *next_x, int *next_y)
{
	*next_x = enemy->x;
	*next_y = enemy->y;
	if (enemy->direction == 'R')
		(*next_y)++;
	else if (enemy->direction == 'L')
		(*next_y)--;
	else if (enemy->direction == 'D')
		(*next_x)++;
	else if (enemy->direction == 'U')
		(*next_x)--;
}

void	ft_teletransport(t_map *game)
{
	size_t	x;
	size_t	y;
	size_t	current_x;
	size_t	current_y;

	current_x = game->player.x;
	current_y = game->player.y;

	x = 0;
	while (x < game->height)
	{
		y = 0;
		while (y < game->width)
		{
			if (game->map[x][y] == 'T' && !(x == current_x && y == current_y))
			{
				game->player.x = x;
				game->player.y = y;
				game->count++;
				ft_print_map(game);
				put_movements(game);
				ft_printf("Teleported! Movements: %d\n", game->count);
				return ;
			}
			y++;
		}
		x++;
	}
}

/* void	ft_teletransport(t_map *game)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < game->height)
	{
		y = 0;
		while (y < game->width)
		{
			if (game->map[x][y] == 'T')
			{
				game->map[game->player.x][game->player.y] = '0';
				game->player.x = x;
				game->player.y = y;
				game->map[game->player.x][game->player.y] = 'P';
				game->count++;
				ft_print_map(game);
				put_movements(game);
				ft_printf("Teleported! Movements: %d\n", game->count);
				return ;
			}
			y++;
		}
		x++;
	}
}


 */
