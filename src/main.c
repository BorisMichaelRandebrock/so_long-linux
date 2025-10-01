/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:26:44 by brandebr          #+#    #+#             */
/*   Updated: 2025/10/01 09:22:27 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "so_long.h"
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

void	register_hooks(t_map *game)
{
	mlx_loop_hook(game->mlx_ptr, enemy_update, game);
	mlx_hook(game.win_ptr, 2, 0, ft_move, &game);
	mlx_hook(game.win_ptr, 17, 0, ft_close, &game);
	// mlx_hook(game->win_ptr, 2, 1L << 0, ft_move, game);
	// mlx_hook(game->win_ptr, 17, 1L << 17, ft_close, game);
}

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

int	main(int argc, char **argv)
{
	t_map	game;
	int		fd;
	int		start_level;

	init_game(&game, argc, argv);
	load_levels(&game);
	start_level = parse_it(argc, argv, game.total_levels);
	if (start_level == -1)
		load_level_without_clear(&game, argv[1]);
	else
	{
		game.current_level = start_level;
		load_level_without_clear(&game, game.level_files[game.current_level]);
	}
	fd = open(game.level_files[game.current_level], O_RDONLY);
	if (fd == -1)
		exit_error(NULL, "ERROR\nWrong file reading\n", 1);
	close(fd);
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.width * SIZE,
			game.height * SIZE, "a link to the past..");
	if (game.win_ptr == NULL)
		exit_error(NULL, "ERROR\nUnable to create a window\n", 1);
	print_map_reg_hooks(&game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
/* asd(&game);

void asd(t_map *game) {
	ft_printf("Maps flooded\n");
   tokemo(game->map,0);
   ft_printf("\n");
   tokemo(game->map_cpy,0);
   ft_printf("\n");
}
 */
