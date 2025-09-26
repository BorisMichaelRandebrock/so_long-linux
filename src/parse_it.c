/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:18:47 by brandebr          #+#    #+#             */
/*   Updated: 2024/01/04 16:47:45 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	file_name(char *fn)
{
	char	*end;
	int		i;
	int		j;

	i = 0;
	j = 0;
	end = ".ber";
	while (fn[i])
		i++;
	i = i - 4;
	while (fn[i])
	{
		if (fn[i++] == end[j++])
			continue ;
		else
			return (-1);
	}
	return (0);
}
/*
int	parse_it(int argc, char **argv)
{
	int		fd;
	char	buffer;
	ssize_t	bytes_read;

	fd = (open(argv[1], O_RDONLY));
	bytes_read = read(fd, &buffer, 1);
	if (argc != 1 && argc != 2)
		exit_error(NULL, "ERROR\nIncorrect number of arguments\n", 1);
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		bytes_read = read(fd, &buffer, 1);
		if (fd == -1)
			exit_error(NULL, "ERROR\nWrong file reading\n", 1);
		else if (file_name(argv[1]) == -1)
			exit_error(NULL, "ERROR\nWrong file type\n", 1);
		else if (fd > 0 && bytes_read == 0)
			exit_error(NULL, "ERROR\nEmpty file\n", 1);
		close(fd);
	}
	return (0);
}
 */

int	parse_it(int argc, char **argv, int total_levels)
{
	int		fd;
	int		i;
	int		level;
	char	buffer;
	ssize_t	bytes_read;

	if (argc != 1 && argc != 2)
		exit_error(NULL, "ERROR\nIncorrect number of arguments\n", 1);
	if (argc == 1)
		return (0);
	i = -1;
	while (argv[1][++i])
		if (argv[1][i] < '0' || argv[1][i] > '9')
			break ;
	if (i > 0 && argv[1][i] == '\0')
	{
		i = -1;
		level = 0;
		while (argv[1][++i])
			level = level * 10 + (argv[1][i] - '0');
		if (level >= 0 && level < total_levels)
			return (level);
		exit_error(NULL, "ERROR\nLevel index out of range\n", 1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_error(NULL, "ERROR\nWrong file reading\n", 1);
	bytes_read = read(fd, &buffer, 1);
	if (file_name(argv[1]) == -1)
		exit_error(NULL, "ERROR\nWrong file type\n", 1);
	if (bytes_read == 0)
		exit_error(NULL, "ERROR\nEmpty file\n", 1);
	close(fd);
	return (-1);
}

int	exit_player_check(t_map *game)
{
	unsigned long	y;
	unsigned long	x;
	int				player;
	int				exit;

	x = 0;
	y = 0;
	player = 0;
	exit = 0;
	while ((y < game->height) && (x < game->width))
	{
		if (game->map[y][x] == 'E')
			exit++;
		if (game->map[y][x] == 'P')
			player++;
		y++;
		if (y == game->height)
		{
			x++;
			y = 0;
		}
	}
	if (player != 1 || exit != 1)
		return (-1);
	return (0);
}

int	ft_collectibles(t_map *game)
{
	size_t	y;
	size_t	x;
	int		count;

	x = 0;
	y = 0;
	count = 0;
	while (y < game->height && x < game->width)
	{
		if (game->map[y][x] == 'C')
			count++;
		else if (ft_cant(game->map[y][x]) == -1)
			return (-1);
		y++;
		if (y == game->height)
		{
			x++;
			y = 0;
		}
	}
	if (count < 1)
		return (-1);
	game->coins = count;
	game->coins_cpy = count;
	return (0);
}

void	ft_rectangle_check(t_map *game)
{
	unsigned long	y;
	int				a;
	int				b;

	y = 0;
	a = ft_strlen(game->map[y]);
	if (game->map[y][a - 1] == '\n')
		a -= 1;
	while (y < game->height)
	{
		b = ft_strlen(game->map[y]);
		if (game->map[y][b - 1] == '\n')
			b -= 1;
		if (b == a)
			y++;
		else
			exit_error(game, "Error\nThe map is not a square\n", 0);
	}
}
