/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@42barcelona.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:35:50 by brandebr          #+#    #+#             */
/*   Updated: 2025/09/24 13:35:53 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "so_long.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void	init_game(t_map *game, int argc, char **argv)
{
	rand();
	game->count = 0;
	game->enemy_frame = 0;
	game->last_move_time = get_time_ms();
	game->current_level = 0;
	game->map = NULL;
	game->map_cpy = NULL;
	game->mlx_ptr = NULL;
	if (argc == 2)
		parse_it(argc, argv);
	else if (argc != 1)
		exit_error(NULL, "ERROR\nIncorrect number of arguments\n", 1);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		exit_error(NULL, "ERROR\nFailed to initialize MLX\n", 1);
	game->level_files = malloc(sizeof(char *) * 10);
	if (!game->level_files)
		exit_error(NULL, "ERROR\nFailed to allocate memory 4 level files\n", 1);
}

void	load_levels(t_map *game)
{
	char	*level_names[10];
	int		i;

	level_names[0] = "maps/new.ber";
	level_names[1] = "maps/min_ex.ber";
	level_names[2] = "maps/generated.ber";
	level_names[3] = "maps/some2.ber";
	level_names[4] = "maps_bonus/some.ber";
	level_names[5] = "maps_bonus/warp.ber";
	level_names[6] = "maps_bonus/maze.ber";
	level_names[7] = "maps_bonus/spirall.ber";
	level_names[8] = "maps_bonus/batcave.ber";
	level_names[9] = NULL;
	i = -1;
	game->total_levels = 0;
	while (level_names[++i] != NULL)
	{
		game->level_files[i] = ft_strdup(level_names[i]);
		if (!game->level_files[i])
			exit_error(NULL, "ERROR\nFailed to duplicate level filename\n", 1);
		game->total_levels++;
	}
	game->level_files[i] = NULL;
}
