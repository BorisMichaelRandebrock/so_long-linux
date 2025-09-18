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
	for (frame = 0; frame < 5; frame++)
	{
		game->enemy_img[0][frame] = mlx_xpm_file_to_image(game->mlx_ptr,
				frame_paths[frame], &width, &height);
		if (!game->enemy_img[0][frame])
			exit_error(game, "Error\nFailed to load enemy animation frame\n",
				0);
	}
}
