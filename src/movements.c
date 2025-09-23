/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:11:19 by brandebr          #+#    #+#             */
/*   Updated: 2024/01/10 14:25:21 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_move_w(t_map *game)
{
	game->direction = 'W';
	if (game->map[game->player.x - 1][game->player.y] == 'E'
		&& game->coins == 0)
	{
		game->map[game->player.x][game->player.y] = '0';
		ft_printf("YOU WON!!! 🥳\n");
		ft_win(game);
	}
	if (game->map[game->player.x - 1][game->player.y] == 'T')
		{
			game->map[game->player.x][game->player.y] = '0';
			game->player.x = game->player.x - 1;
			//game->map[game->player.x][game->player.y] = 'T';
			ft_teletransport(game);
			ft_print_map(game);
			ft_enemy_touched(game);
			return (0);
		}
	if ((game->map[game->player.x - 1][game->player.y] != '1')
		&& game->map[game->player.x - 1][game->player.y] != 'E')
	{
		if (game->map[game->player.x - 1][game->player.y] == 'C')
			game->coins--;
		game->map[game->player.x][game->player.y] = '0';
		game->player.x = game->player.x - 1;
		game->map[game->player.x][game->player.y] = 'P';
		game->count++;
		ft_print_map(game);
		put_movements(game);
		ft_printf("Movements: %d\n", game->count);
		ft_enemy_touched(game);
	}
	return (0);
}

static int	ft_move_s(t_map *game)
{
	game->direction = 'S';
	if ((game->coins == 0) && game->map[game->player.x
			+ 1][game->player.y] == 'E')
	{
		game->map[game->player.x][game->player.y] = '0';
		ft_printf("YOU 🗽 WON!!!\n");
		ft_win(game);
	}
	if (game->map[game->player.x + 1][game->player.y] == 'T')
		{
			game->map[game->player.x][game->player.y] = '0';
			game->player.x = game->player.x + 1;
			//game->map[game->player.x][game->player.y] = 'T';
			ft_teletransport(game);
			ft_print_map(game);
			ft_enemy_touched(game);
			return (0);
		}
	if ((game->map[game->player.x + 1][game->player.y] != '1')
		&& game->map[game->player.x + 1][game->player.y] != 'E')
	{
		if (game->map[game->player.x + 1][game->player.y] == 'C')
			game->coins--;
		game->map[game->player.x][game->player.y] = '0';
		game->player.x = game->player.x + 1;
		game->map[game->player.x][game->player.y] = 'P';
		game->count++;
		ft_print_map(game);
		put_movements(game);
		ft_printf("Movements: %d\n", game->count);
		ft_enemy_touched(game);
	}
	return (0);
}

static int	ft_move_a(t_map *game)
{
	game->direction = 'A';
	if ((game->map[game->player.x][game->player.y - 1] == 'E'
		&& game->coins == 0))
	{
		game->map[game->player.x][game->player.y] = '0';
		ft_printf("🥇 YOU WON!!!\n");
		ft_win(game);
	}
	if (game->map[game->player.x][game->player.y - 1] == 'T')
		{
			game->map[game->player.x][game->player.y] = '0';
			game->player.y = game->player.y - 1;
			//game->map[game->player.x][game->player.y] = 'T';
			ft_teletransport(game);
			ft_print_map(game);
			ft_enemy_touched(game);
			return (0);
		}
	if ((game->map[game->player.x][game->player.y - 1] != '1')
		&& game->map[game->player.x][game->player.y - 1] != 'E')
	{
		if (game->map[game->player.x][game->player.y - 1] == 'C')
			game->coins--;
		game->map[game->player.x][game->player.y] = '0';
		game->player.y = game->player.y - 1;
		game->map[game->player.x][game->player.y] = 'P';
		game->count++;
		ft_print_map(game);
		put_movements(game);
		ft_printf("Movements: %d\n", game->count);
		ft_enemy_touched(game);
	}
	return (0);
}

static int	ft_move_d(t_map *game)
{
	game->direction = 'D';
	if ((game->map[game->player.x][game->player.y + 1] == 'E'
		&& game->coins == 0))
	{
		game->map[game->player.x][game->player.y] = '0';
		ft_printf("YOU WON!!! 🧸\n");
		ft_win(game);
	}
	if (game->map[game->player.x][game->player.y + 1] == 'T')
		{
			game->map[game->player.x][game->player.y] = '0';
			game->player.y = game->player.y + 1;
			//game->map[game->player.x][game->player.y] = 'T';
			ft_teletransport(game);
			ft_print_map(game);
			ft_enemy_touched(game);
			return (0);
		}
	if ((game->map[game->player.x][game->player.y + 1] != '1')
		&& game->map[game->player.x][game->player.y + 1] != 'E')
	{
		if (game->map[game->player.x][game->player.y + 1] == 'C')
			game->coins--;
		game->map[game->player.x][game->player.y] = '0';
		game->player.y = game->player.y + 1;
		game->map[game->player.x][game->player.y] = 'P';
		game->count++;
		ft_print_map(game);
		put_movements(game);
		ft_printf("Movements: %d\n", game->count);
		ft_enemy_touched(game);
	}
	return (0);
}

int	ft_move(int keycode, t_map *game)
{
	if (keycode == 119 || keycode == 65362)
		ft_move_w(game);
	if (keycode == 97 || keycode == 65361)
		ft_move_a(game);
	if (keycode == 115 || keycode == 65364)
		ft_move_s(game);
	if (keycode == 100 || keycode == 65363)
		ft_move_d(game);
	if (keycode == 65307)
		exit(1);
	return (0);
}
