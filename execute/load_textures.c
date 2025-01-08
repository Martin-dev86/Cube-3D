#include "../Includes/cub3d.h"

void error(void)
{
    puts(mlx_strerror(mlx_errno));
    printf("Es aquí\n");
    exit(EXIT_FAILURE);
}
void load_walls(t_game *game)
{
    xpm_t *xpm;

    xpm = mlx_load_xpm42("textures/barrel.xpm42");
    if (!xpm)
        error();
    game->textures.north = &xpm->texture;

    xpm = mlx_load_xpm42("textures/eagle.xpm42");
    if (!xpm)
        error();
    game->textures.south = &xpm->texture;

    xpm = mlx_load_xpm42("textures/mossy.xpm42");
    if (!xpm)
        error();
    game->textures.west = &xpm->texture;

    xpm = mlx_load_xpm42("textures/redbrick.xpm42");
    if (!xpm)
        error();
    game->textures.east = &xpm->texture;
}
