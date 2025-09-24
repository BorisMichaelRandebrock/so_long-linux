/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@42barcelona.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:29:42 by brandebr          #+#    #+#             */
/*   Updated: 2025/09/24 12:29:45 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "so_long.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void	load_level(t_map *game, char *level_file)
{
	char	*argv[3];

	if (game->map)
	{
		cleanup_images(game);
		ft_free_map(game);
	}
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	game->count = 0;
	game->coins = 0;
	game->coins_cpy = 0;
	argv[0] = "./so_long";
	argv[1] = level_file;
	argv[2] = NULL;
	ft_read_map(argv, game);
	ft_measures(game);
	map_check(game);
	player_position(game);
	ft_upload_img(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->width * SIZE,
			game->height * SIZE, "a link to the past..");
	if (game->win_ptr == NULL)
		exit_error(game, "ERROR\nUnable to create window for new level\n", 0);
	register_hooks(game);
}

void	load_level_without_clear(t_map *game, char *level_file)
{
	char	*argv[3];

	if (game->map)
		ft_free_map(game);
	game->count = 0;
	game->coins = 0;
	game->coins_cpy = 0;
	argv[0] = "./so_long";
	argv[1] = level_file;
	argv[2] = NULL;
	ft_read_map(argv, game);
	ft_measures(game);
	map_check(game);
	player_position(game);
	ft_upload_img(game);
}

void	tokemo(char **arr, int line)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		printf("%s", arr[i]);
		if (line)
			printf("\n");
		i++;
	}
}

void	cleanup_images(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 9)
	{
		if (game->imgs[i].img_ptr)
		{
			mlx_destroy_image(game->mlx_ptr, game->imgs[i].img_ptr);
			game->imgs[i].img_ptr = NULL;
		}
		i++;
	}
	i = 0;
	while (i < 1)
	{
		j = 0;
		while (j < 5)
		{
			if (game->enemy_img[i][j])
			{
				mlx_destroy_image(game->mlx_ptr, game->enemy_img[i][j]);
				game->enemy_img[i][j] = NULL;
			}
			j++;
		}
		i++;
	}
}
