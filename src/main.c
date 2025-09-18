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

#include "so_long.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void	exit_error(t_map *game, char *str, int mod)
{
	size_t	size;

	size = ft_strlen(str);
	if (!mod)
		ft_free_map(game);
	write(2, str, size);
	exit(1);
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

void	ft_win(t_map *game)
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

int	main(int argc, char **argv)
{
	t_map	game;

	rand();
	game.count = 0;
	game.enemy_frame = 0;
	parse_it(argc, argv);
	ft_read_map(argv, &game);
	ft_measures(&game);
	map_check(&game);
	game.mlx_ptr = mlx_init();
	ft_upload_img(&game);
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.width * SIZE, game.height
			* SIZE, "a link to the past..");
	if (game.win_ptr == NULL)
		exit_error(NULL, "ERROR\nUnable to create a window\n", 1);
	ft_print_map(&game);
	mlx_loop_hook(game.mlx_ptr, enemy_update, &game);
	mlx_hook(game.win_ptr, 2, 1L << 0, ft_move, &game);
	mlx_hook(game.win_ptr, 17, 1L << 17, ft_close, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
