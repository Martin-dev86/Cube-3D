#include "../Includes/cub3d.h"

void error(char *str, t_game *game)
{
    printf("Error: %s\n", str);
    free_map(game->worldMap, game->mapHeight);
    mlx_close_window(game->mlx);
    exit(EXIT_FAILURE);
}
