/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:26:44 by brandebr          #+#    #+#             */
/*   Updated: 2024/01/04 16:46:39 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "so_long.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void	ft_upload_warp(t_map *game, int height, int width)
{
	game->imgs[8].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"imgs/warp2.xpm", &width, &height);
	if (!game->imgs[8].img_ptr)
		exit_error(game, "Error\nFailed to load warp sprite\n", 0);
	game->imgs[8].data = (int *)mlx_get_data_addr(game->imgs[8].img_ptr,
			&game->imgs[8].bpp, &game->imgs[8].size_l, &game->imgs[8].endian);
}

void	player_position(t_map *game)
{
	game->player.x = 0;
	game->player.y = 0;
	while (game->player.y <= game->height && game->player.x <= game->width)
	{
		if (game->map[game->player.y][game->player.x] == 'P')
			return ;
		game->player.x++;
		if (game->player.x == game->width)
		{
			game->player.x = 0;
			game->player.y++;
		}
	}
}

/* void	load_level(t_map *game, char *level_file)
{
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
	char *argv[3];
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
} */

/* void	cleanup_images(t_map *game)
{
	int i, j;

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
} */

void	register_hooks(t_map *game)
{
	mlx_loop_hook(game->mlx_ptr, enemy_update, game);
	mlx_hook(game->win_ptr, 2, 1L << 0, ft_move, game);
	mlx_hook(game->win_ptr, 17, 1L << 17, ft_close, game);
}

/* void	load_level_without_clear(t_map *game, char *level_file)
{
	if (game->map)
		ft_free_map(game);

	game->count = 0;
	game->coins = 0;
	game->coins_cpy = 0;

	char *argv[3];
	argv[0] = "./so_long";
	argv[1] = level_file;
	argv[2] = NULL;

	ft_read_map(argv, game);
	ft_measures(game);
	map_check(game);
	player_position(game);

	ft_upload_img(game);
} */

void	ft_win(t_map *game)
{
	int	wd_w;
	int	wd_h;

	game->count++;
	ft_printf("Level %d completed! Total movements: %d\n", game->current_level
		+ 1, game->count);
	if (game->current_level + 1 < game->total_levels)
	{
		game->current_level++;
		ft_printf("Loading Level %d...\n", game->current_level + 1);
		load_level(game, game->level_files[game->current_level]);
		ft_print_map(game);
	}
	else
	{
		wd_w = game->width * SIZE;
		wd_h = game->height * SIZE;
		mlx_string_put(game->mlx_ptr, game->win_ptr,
			(wd_w / 2) - 100, wd_h / 2, 0x00FF00, "CONGRATS! GAME COMPLETED!");
		mlx_do_sync(game->mlx_ptr);
		sleep(3);
		ft_close(game);
	}
}

/* void	tokemo(char **arr, int line)
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
 */
int	main(int argc, char **argv)
{
	t_map	game;
	int		fd;

	rand();
	game.count = 0;
	game.enemy_frame = 0;
	game.last_move_time = get_time_ms();
	game.current_level = 0;
	game.map = NULL;
	game.map_cpy = NULL;
	game.mlx_ptr = NULL;
	if (argc == 2)
		parse_it(argc, argv);
	else if (argc != 1)
		exit_error(NULL, "ERROR\nIncorrect number of arguments\n", 1);
	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
		exit_error(NULL, "ERROR\nFailed to initialize MLX\n", 1);
	game.level_files = malloc(sizeof(char *) * 10);
	if (!game.level_files)
		exit_error(NULL, "ERROR\nFailed to allocate memory 4 level files\n", 1);
	game.total_levels = 0;
	game.level_files[game.total_levels++] = ft_strdup("maps/new.ber");
	if (!game.level_files[game.total_levels - 1])
		exit_error(NULL, "ERROR\nFailed to duplicate level filename\n", 1);
	game.level_files[game.total_levels++] = ft_strdup("maps/min_ex.ber");
	if (!game.level_files[game.total_levels - 1])
		exit_error(NULL, "ERROR\nFailed to duplicate level filename\n", 1);
	game.level_files[game.total_levels++] = ft_strdup("maps/generated.ber");
	if (!game.level_files[game.total_levels - 1])
		exit_error(NULL, "ERROR\nFailed to duplicate level filename\n", 1);
	game.level_files[game.total_levels++] = ft_strdup("maps/some2.ber");
	if (!game.level_files[game.total_levels - 1])
		exit_error(NULL, "ERROR\nFailed to duplicate level filename\n", 1);
	game.level_files[game.total_levels++] = ft_strdup("bonus_maps/some.ber");
	if (!game.level_files[game.total_levels - 1])
		exit_error(NULL, "ERROR\nFailed to duplicate level filename\n", 1);
	game.level_files[game.total_levels++] = ft_strdup("bonus_maps/warp.ber");
	if (!game.level_files[game.total_levels - 1])
		exit_error(NULL, "ERROR\nFailed to duplicate level filename\n", 1);
	game.level_files[game.total_levels++] = ft_strdup("bonus_maps/maze.ber");
	if (!game.level_files[game.total_levels - 1])
		exit_error(NULL, "ERROR\nFailed to duplicate level filename\n", 1);
	game.level_files[game.total_levels++] = ft_strdup("bonus_maps/spirall.ber");
	if (!game.level_files[game.total_levels - 1])
		exit_error(NULL, "ERROR\nFailed to duplicate level filename\n", 1);
	game.level_files[game.total_levels++] = ft_strdup("bonus_maps/batcave.ber");
	if (!game.level_files[game.total_levels - 1])
		exit_error(NULL, "ERROR\nFailed to duplicate level filename\n", 1);
	game.level_files[game.total_levels] = NULL;
	load_level_without_clear(&game, game.level_files[game.current_level]);
	fd = open(game.level_files[game.current_level], O_RDONLY);
	if (fd == -1)
		exit_error(NULL, "ERROR\nWrong file reading\n", 1);
	close(fd);
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.width * SIZE,
			game.height * SIZE, "a link to the past..");
	if (game.win_ptr == NULL)
		exit_error(NULL, "ERROR\nUnable to create a window\n", 1);
	ft_print_map(&game);
	register_hooks(&game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
