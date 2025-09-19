/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:37:49 by brandebr          #+#    #+#             */
/*   Updated: 2025/09/19 15:02:57 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_map(t_map *game, size_t x, size_t y)
{
	if (x < 0 || y < 0 || x >= game->height || y >= game->width)
		return ;
	if (game->map_cpy[x][y] == 'V' || game->map_cpy[x][y] == '1'
		|| game->map_cpy[x][y] == 'E')
		return ;
	game->map_cpy[x][y] = 'V';
	flood_map(game, x + 1, y);
	flood_map(game, x - 1, y);
	flood_map(game, x, y + 1);
	flood_map(game, x, y - 1);
}

void	ft_check_exit(t_map *game)
{
	int	x;
	int	y;

	x = 0;
	while (game->map_cpy[x])
	{
		y = 0;
		while (game->map_cpy[x][y])
		{
			if (game->map_cpy[x][y] == 'C')
				exit_error(game,
					"ERROR\nOne or more collectables "
					"are not reachable\n",
					0);
			else if (game->map_cpy[x][y] == 'E' && game->map_cpy[x
				- 1][y] != 'V' && game->map_cpy[x + 1][y] != 'V'
				&& game->map_cpy[x][y - 1] != 'V' && game->map_cpy[x][y
				+ 1] != 'V')
				exit_error(game, "ERROR\nExit not reachable\n", 0);
			y++;
		}
		x++;
	}
}
