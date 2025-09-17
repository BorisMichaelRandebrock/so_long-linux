/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:17:48 by brandebr          #+#    #+#             */
/*   Updated: 2024/06/14 23:23:48 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include "Libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "mlx/mlx.h"
# define SIZE 32

typedef struct s_img
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_pos
{
	size_t	x;
	size_t	y;
}				t_pos;

typedef struct s_enemy
{
	size_t	x;
	size_t	y;
	char		direction;
	int			frame;
	int			step_count;
}				t_enemy;

typedef struct s_map
{
	char		*raw_map;
	char		**map;
	char		**map_cpy;
	char		**map_cpy2;
	char		**path;
	size_t	height;
	size_t	width;
	size_t	coins;
	size_t	coins_cpy;
	t_pos		player;
	int			count;
	int			flag;
	t_pos		start;
	int			exit;
	void		*mlx_ptr;
	void		*win_ptr;  
	t_img		*imgs;
	size_t	x;
	size_t	y;
	char		direction;
	t_enemy	*enemies;
	int			enemy_count;
	void		*enemy_img[4][5];
	int			enemy_frame;
}					t_map;


void	exit_error(t_map *game, char *str, int mod);//main.c
void	player_position(t_map *game);//main.c
void	ft_win(t_map *game);//main
void	tokemo(char **arr, int line);//main
int		file_name(char *fn);// parse_it.c
int		parse_it(int argc, char **argv);// parse_it.c
int		exit_player_check(t_map *game);//parse_it.c
int		ft_collectibles(t_map *game);//parse_it.c
void	ft_rectangle_check(t_map *game);// paarse_it.c	
void	ft_read_map(char **argv, t_map *game); //ft_read_map.c
void	map_check(t_map *game);//read_map.c
void	ft_free_map(t_map *game);//ft_read_map.c
void	ft_measures(t_map *game);//ft_read_map.c
int		ft_outer_limits(t_map *game);//read_map.c
int		ft_move(int keycode, t_map *game);//movements.c
void	flood_map(t_map *map, size_t x, size_t y);//flood_map.c
void	ft_check_exit(t_map *game);//flood_map
void	ft_upload_more(t_map *game, int height, int width);
void	ft_upload_img(t_map *game);//upload_img
int		ft_print_map(t_map *game);//upload_img
int		ft_cant(char c); //upload_img.c
int		ft_player_position(int count1, int count2, t_map *game);//position.c
int		ft_o_position(int count1, int count2, t_map *game);//position
int		ft_wall_position(int count1, int count2, t_map *game);//position 
int		ft_exit_position(int count1, int count2, t_map *game);// positione
int		ft_collect_position(int count1, int count2, t_map *game);//position
int		ft_fake_position(int count1, int count2, t_map *game);//upload_img
int		ft_close(t_map *game);//exit
void	ft_enemy_touched(t_map *game);//movements.c
void	put_movements(t_map *game);//movements.c
void	parse_enemies(t_map *game);//parse_it.c
void	draw_enemies(t_map *game);//upload_img.c
void	animate_enemies(t_map *game);//bonus.c
int		enemy_update(void *param);//bonus.c
void	move_enemies(t_map *game);//bonus.c
#endif
