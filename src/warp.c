/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@42barcelona.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:00:16 by brandebr          #+#    #+#             */
/*   Updated: 2025/09/23 13:00:21 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	teletransport_help(t_map *game)
{
	ft_print_map(game);
	put_movements(game);
	ft_printf("Teleported! Movements: %d\n", game->count);
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
				teletransport_help(game);
			}
			y++;
		}
		x++;
	}
}

void	move_util(t_map *game)
{
	game->map[game->player.x][game->player.y] = 'P';
	game->count++;
	ft_print_map(game);
	put_movements(game);
	ft_printf("Movements: %d\n", game->count);
	ft_enemy_touched(game);
}

void	warp_helper(t_map *game)
{
	ft_teletransport(game);
	ft_print_map(game);
	ft_enemy_touched(game);
}

int	ft_warp_position(int count1, int count2, t_map *game)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->imgs[8].img_ptr, (count2 * SIZE), (count1 * SIZE));
	return (0);
}
