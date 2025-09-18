/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:28:26 by brandebr          #+#    #+#             */
/*   Updated: 2024/01/04 13:09:54 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//@@@ Tobe continued
static void	fill_rect_helper(int *data, t_rect *rect, int color,
	void *mlx_ptr_unused)
{
	int	bpp;
	int	size_l;
	int	endian;
	int	i;
	int	j;

	mlx_get_data_addr(mlx_ptr_unused, &bpp, &size_l, &endian);
	i = 0;
	while (i < rect->h)
	{
		j = 0;
		while (j < rect->w)
		{
			data[i * (size_l / 4) + j] = color;
			j++;
		}
		i++;
	}
}

void	mlx_rectangle(void *mlx_ptr, void *win_ptr, t_rect *rect, int color)
{
	void	*img;
	int		*data;
	int		bpp;
	int		size_l;
	int		endian;

	img = mlx_new_image(mlx_ptr, rect->w, rect->h);
	data = (int *)mlx_get_data_addr(img, &bpp, &size_l, &endian);
	fill_rect_helper(data, rect, color, mlx_ptr);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img, rect->x, rect->y);
	mlx_destroy_image(mlx_ptr, img);
}

void	ft_enemy_touched(t_map *game)
{
	int		i;
	t_rect	rect;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->player.x == game->enemies[i].x
			&& game->player.y == game->enemies[i].y)
		{
			ft_printf("GAME OVER! YOU HAVE BEEN CAUGHT BY THE ENEMY! 💀\n");
			rect.x = 0;
			rect.y = 0;
			rect.w = game->width * SIZE;
			rect.h = game->height * SIZE;
			mlx_rectangle(game->mlx_ptr, game->win_ptr, &rect, 0x000000);
			mlx_string_put(game->mlx_ptr, game->win_ptr,
				((game->width * SIZE) / 2) - 170, (game->height * SIZE) / 2,
				0xFF0000, "GAME OVER! YOU HAVE BEEN CAUGHT BY THE ENEMY!");
			mlx_do_sync(game->mlx_ptr);
			sleep(4);
			ft_close(game);
			exit(1);
		}
		i++;
	}
}

int	ft_close(t_map *game)
{
	if (game->enemies)
	{
		free(game->enemies);
		game->enemies = NULL;
	}
	ft_free_map(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
	return (0);
}
