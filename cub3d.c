/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:23:11 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/11 12:13:11 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d.h"

void free_map(char **map, int mapHeight)
{
    int i;

    i = 0;
    while(i < mapHeight)
    {
        free(map[i]);
        i++;
    }
    free(map);
}

char **initialize_map(const char *mapData[], int mapHeight)
{
    char **map;
    int i;
    
    i = 0;
    map = calloc(mapHeight, sizeof(char *));
    if (!map)
        return NULL;
    while (i < mapHeight)
    {
        map[i] = ft_strdup(mapData[i]);
        if (!map[i])
        {
            free_map(map, i);
            return NULL;
        }
        i++;
    }
    return (map);
}

void prep_game(t_game *game)
{
    game->screen_width = SCREENWIDTH;
    game->screen_height = SCREENHEIGHT;
    game->player_pos_x = 1.5;
    game->player_pos_y = 1.5;
    game->player_dir_x = -1;
    game->player_dir_y = 0;
    game->plane_x = 0;
    game->plane_y = 0.66;
}

int main(void)
{
    t_game game;
    const char *mapData[] = {
        "1111111111",
        "10000001",
        "1001001",
        "10000001",
        "1111111111"
    };
    int mapHeight = sizeof(mapData) / sizeof(mapData[0]);

    // Inicializar el mapa
    game.worldMap = initialize_map(mapData, mapHeight);
    if (!game.worldMap)
        error("no se pudo inicializar el mapa", &game);
    // Configurar la estructura de juego y MLX
    prep_game(&game);
    mlx_t *mlx = mlx_init(game.screen_width, game.screen_height, "Cub3D", true);
    if (!mlx)
        error("no se pudo inicializar MLX", &game);
    game.mlx = mlx;

    game.image = mlx_new_image(mlx, game.screen_width, game.screen_height);
    if (!game.image)
        error("no se pudo crear la imagen", &game);
    // Cargar texturas
    load_walls(&game);

    // Configurar hooks y bucle principal
    mlx_loop_hook(game.mlx, &render_walls, &game);
    mlx_key_hook(game.mlx, &move_player, &game);
    mlx_loop(game.mlx);

    // Liberar recursos
    free_map(game.worldMap, mapHeight);
    mlx_terminate(game.mlx);
    return (0);
}
