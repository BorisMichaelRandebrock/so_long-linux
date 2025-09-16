/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:44:48 by brandebr          #+#    #+#             */
/*   Updated: 2024/01/10 14:25:23 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_fake_position(int count1, int count2, t_map *game)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->imgs[1].img_ptr, (count2 * SIZE), (count1 * SIZE));
	return (0);
}

void ft_upload_enemies(t_map *game, int height, int width)
{
	char	*frame_paths[5] = {
		"imgs/Enemy/Anim/Bat_0.xpm",
		"imgs/Enemy/Anim/Bat_1.xpm",
		"imgs/Enemy/Anim/Bat_2.xpm",
		"imgs/Enemy/Anim/Bat_3.xpm",
		"imgs/Enemy/Anim/Bat_4.xpm"
	};

	for (int frame = 0; frame < 5; frame++)  // 5 frames
	{
		game->enemy_img[0][frame] = mlx_xpm_file_to_image(game->mlx_ptr, frame_paths[frame], &width, &height);
		if (!game->enemy_img[0][frame])
			exit_error(game, "Error\nFailed to load enemy animation frame\n", 0);
	}
}

void	ft_upload_more(t_map *game, int height, int width)
{
	game->imgs[4].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"imgs/collect.xpm", &width, &height);
	game->imgs[4].data = (int *)mlx_get_data_addr(game->imgs[4].img_ptr,
			&game->imgs[4].bpp, &game->imgs[4].size_l, &game->imgs[4].endian);
	game->imgs[5].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"imgs/player_left.xpm", &width, &height);
	game->imgs[5].data = (int *)mlx_get_data_addr(game->imgs[5].img_ptr,
			&game->imgs[5].bpp, &game->imgs[5].size_l, &game->imgs[5].endian);
	game->imgs[6].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"imgs/player_up.xpm", &width, &height);
	game->imgs[6].data = (int *)mlx_get_data_addr(game->imgs[6].img_ptr,
			&game->imgs[6].bpp, &game->imgs[6].size_l, &game->imgs[6].endian);
	game->imgs[7].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"imgs/player_down.xpm", &width, &height);
	game->imgs[7].data = (int *)mlx_get_data_addr(game->imgs[7].img_ptr,
			&game->imgs[7].bpp, &game->imgs[7].size_l, &game->imgs[7].endian);

}

void	ft_upload_img(t_map *game)
{
	int		height;
	int		width;

	game->imgs = malloc(sizeof(t_img) * 8);
	game->imgs[0].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"imgs/0.xpm", &width, &height);
	game->imgs[0].data = (int *)mlx_get_data_addr(game->imgs[0].img_ptr,
			&game->imgs[0].bpp, &game->imgs[0].size_l, &game->imgs[0].endian);
	game->imgs[1].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"imgs/1.xpm", &width, &height);
	game->imgs[1].data = (int *)mlx_get_data_addr(game->imgs[1].img_ptr,
			&game->imgs[1].bpp, &game->imgs[1].size_l, &game->imgs[1].endian);
	game->imgs[2].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"imgs/exit.xpm", &width, &height);
	game->imgs[2].data = (int *)mlx_get_data_addr(game->imgs[2].img_ptr,
			&game->imgs[2].bpp, &game->imgs[2].size_l, &game->imgs[2].endian);
	game->imgs[3].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"imgs/player.xpm", &width, &height);
	game->imgs[3].data = (int *)mlx_get_data_addr(game->imgs[3].img_ptr,
			&game->imgs[3].bpp, &game->imgs[3].size_l, &game->imgs[3].endian);
	ft_upload_more(game, height, width);
	ft_upload_enemies(game, height, width);
}

int	ft_print_map(t_map *game)
{
	game->y = 0;
	game->x = 0;
	while (game->y <= game->height && game->x <= game->width)
	{
		if (game->map[game->y][game->x] == '0')
			ft_o_position(game->y, game->x, game);
		else if (game->map[game->y][game->x] == '1')
			ft_wall_position(game->y, game->x, game);
		else if (game->map[game->y][game->x] == 'E')
			ft_exit_position(game->y, game->x, game);
		else if (game->map[game->y][game->x] == 'P')
			ft_player_position(game->y, game->x, game);
		else if (game->map[game->y][game->x] == 'C')
			ft_collect_position(game->y, game->x, game);
		else if (game->map[game->y][game->x] == 'F')
			ft_fake_position(game->y, game->x, game);
		game->y++;
		if (game->y == game->height)
		{
			game->x++;
			game->y = 0;
		}
	}
	return (0);
}

int	ft_cant(char c)
{
	if (c != 'E' && c != 'P' && c != '0' && c != '1'
		&& c != 'F' && c != 'B')
		return (-1);
	return (1);
}

void	draw_enemies(t_map *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		// Draw current animation frame for each enemy
		mlx_put_image_to_window(
			game->mlx_ptr,
			game->win_ptr,
			game->enemy_img[0][game->enemies[i].frame],
			game->enemies[i].y * SIZE,  // x position = column * tile size
			game->enemies[i].x * SIZE   // y position = row * tile size
		);
		i++;
	}
}
