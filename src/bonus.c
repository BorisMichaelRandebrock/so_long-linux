#include "so_long.h"

void	animate_enemies(t_map *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		game->enemies[i].step_count++;
		if (game->enemies[i].step_count >= 3) // Change frame every 3 moves
		{
			game->enemies[i].frame = (game->enemies[i].frame + 1) % 5; // Cycle 0→1→2→3→4→0
			game->enemies[i].step_count = 0;
		}
		i++;
	}
}
