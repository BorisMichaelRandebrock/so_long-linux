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

/* void	ft_win(t_map *game)
{
	int		c;
	int		window_w;
	int		window_h;
	char	*msg;

	msg = "CONGRATULATIONS YOU WIN!!!\n";
	c = 0;
	game->count++;
	ft_printf("Total number of movements: %d\n", game->count);
	window_w = game->width * SIZE;
	window_h = game->height * SIZE;
	mlx_string_put(game->mlx_ptr, game->win_ptr, ((window_w) / 2) - 70, window_h
		/ 2, 0xFFFF00, msg);
	mlx_do_sync(game->mlx_ptr);
	sleep(2);
	ft_close(game);
} */

static void	load_level(t_map *game, char *level_file)
{
	if (game->map)
		ft_free_map(game);

	// Reset game state for new level
	game->count = 0;
	game->coins = 0;
	game->coins_cpy = 0;

	// Create argv array for ft_read_map
	char *argv[3];
	argv[0] = "./so_long";
	argv[1] = level_file;
	argv[2] = NULL;

	// Read and parse new level
	ft_read_map(argv, game);
	ft_measures(game);
	map_check(game);
	player_position(game);

	// Initialize MLX if not already done
	if (!game->mlx_ptr)
		game->mlx_ptr = mlx_init();

	// Upload images for new level
	ft_upload_img(game);
	ft_print_map(game);
}

void	ft_win(t_map *game)
{
	game->count++;
	ft_printf("Level %d completed! Total movements: %d\n", game->current_level + 1, game->count);

	// Check if there's a next level
	if (game->current_level + 1 < game->total_levels)
	{
		game->current_level++;
		ft_printf("Loading Level %d...\n", game->current_level + 1);
		load_level(game, game->level_files[game->current_level]);
		mlx_clear_window(game->mlx_ptr, game->win_ptr);  // ← Add this line
		ft_print_map(game);
	}
	else
	{
		// Game completed - show final message
		int	window_w =  game->width * SIZE;
		int	window_h = game->height * SIZE;
		mlx_string_put(game->mlx_ptr, game->win_ptr,
			(window_w / 2) - 100, window_h / 2, 0x00FF00, "CONGRATULATIONS! GAME COMPLETED!");
		mlx_do_sync(game->mlx_ptr);
		sleep(3);
		ft_close(game);
	}
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

static void load_level_without_clear(t_map *game, char *level_file)
{
    // Free previous level data if exists
    if (game->map)
        ft_free_map(game);

    // Reset game state for new level
    game->count = 0;
    game->coins = 0;
    game->coins_cpy = 0;

    // Create argv array for ft_read_map
    char *argv[3];
    argv[0] = "./so_long";
    argv[1] = level_file;
    argv[2] = NULL;

    // Read and parse new level
    ft_read_map(argv, game);
    ft_measures(game);
    map_check(game);
    player_position(game);

    // Upload images for new level
    ft_upload_img(game);

    // Don't clear window here - it doesn't exist yet
}

int	main(int argc, char **argv)
{
	t_map	game;

	// Initialize game structure
	rand();
    game.count = 0;
    game.enemy_frame = 0;
    game.last_move_time = get_time_ms();
    game.current_level = 0;
    game.map = NULL;
    game.map_cpy = NULL;
    game.mlx_ptr = NULL;

    // Only parse arguments if provided
    //if (argc == 2)
    parse_it(argc, argv);

    game.mlx_ptr = mlx_init();
    if (!game.mlx_ptr)
        exit_error(NULL, "ERROR\nFailed to initialize MLX\n", 1);


	// Allocate memory for level files (9 levels + NULL terminator)
	game.level_files = malloc(sizeof(char *) * 10);  // 9 levels + 1 for NULL
	/* if (!game.level_files)
		exit_error(NULL, "ERROR\nFailed to allocate memory for level files\n", 1);
 */
	game.total_levels = 0;

	// Add level files
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
	game.level_files[game.total_levels++] = ft_strdup("bonus_maps/warp_maze.ber");
	if (!game.level_files[game.total_levels - 1])
		exit_error(NULL, "ERROR\nFailed to duplicate level filename\n", 1);
	game.level_files[game.total_levels++] = ft_strdup("bonus_maps/spiralling.ber");
	if (!game.level_files[game.total_levels - 1])
		exit_error(NULL, "ERROR\nFailed to duplicate level filename\n", 1);
	game.level_files[game.total_levels++] = ft_strdup("bonus_maps/bat_cave.ber");
	if (!game.level_files[game.total_levels - 1])
		exit_error(NULL, "ERROR\nFailed to duplicate level filename\n", 1);
	game.level_files[game.total_levels] = NULL;  // Null-terminate array

	// Parse command line arguments

	load_level_without_clear(&game, game.level_files[game.current_level]);
	//load_level(&game, game.level_files[game.current_level]);
	int fd = open(game.level_files[game.current_level], O_RDONLY);
	if (fd == -1)
		exit_error(NULL, "ERROR\nWrong file reading\n", 1);

	// Load first level

	// Create window
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.width * SIZE, game.height * SIZE, "a link to the past..");
	if (game.win_ptr == NULL)
		exit_error(NULL, "ERROR\nUnable to create a window\n", 1);
	//mlx_clear_window(game.mlx_ptr, game.win_ptr);
	// Set up hooks and start game loop
	ft_print_map(&game);
	mlx_loop_hook(game.mlx_ptr, enemy_update, &game);
	mlx_hook(game.win_ptr, 2, 1L << 0, ft_move, &game);
	mlx_hook(game.win_ptr, 17, 1L << 17, ft_close, &game);
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
