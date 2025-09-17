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
