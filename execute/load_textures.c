#include "../Includes/cub3d.h"

void error(char *str,t_game *game)
{
    printf("Error: %s\n", str);
    if (game->worldMap)
        free_map(game->worldMap, game->mapHeight);
    if(game->mlx)
        mlx_close_window(game->mlx);
    exit(EXIT_FAILURE);
}

void load_walls(t_game *game)
{
    xpm_t *xpm;

    xpm = mlx_load_xpm42("textures/barrel.xpm42");
    if (!xpm)
        error("texture not found", game);
    game->textures.north = &xpm->texture;

    xpm = mlx_load_xpm42("textures/eagle.xpm42");
    if (!xpm)
        error("texture not found", game);
    game->textures.south = &xpm->texture;

    xpm = mlx_load_xpm42("textures/mossy.xpm42");
    if (!xpm)
        error("texture not found", game);
    game->textures.west = &xpm->texture;

    xpm = mlx_load_xpm42("textures/redbrick.xpm42");
    if (!xpm)
        error("texture not found", game);
    game->textures.east = &xpm->texture;
}
