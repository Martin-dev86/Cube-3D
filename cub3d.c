/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:23:11 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/08 19:55:48 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d.h"

void free_map(char **map, int mapHeight)
{
    for (int i = 0; i < mapHeight; i++)
        free(map[i]);
    free(map);
}

char **initialize_map(const char *mapData[], int mapHeight)
{
    char **map;

    map = malloc(mapHeight * sizeof(char *));
    if (!map)
        return (NULL);
    for (int i = 0; i < mapHeight; i++)
    {
        map[i] = strdup(mapData[i]);
        if (!map[i])
        {
            free_map(map, i);
            return (NULL);
        }
    }
    return (map);
}

int main(void)
{
    t_game game;
    const char *mapData[] = {
        "1111111111",
        "1000000001",
        "1000010001",
        "1000100001",
        "1000100001",
        "1000010001",
        "1000100001",
        "1000010001",
        "1000000001",
        "1111111111"
    };
    int mapHeight = sizeof(mapData) / sizeof(mapData[0]);

    // Inicializar el mapa
    game.worldMap = initialize_map(mapData, mapHeight);
    if (!game.worldMap)
    {
        fprintf(stderr, "Error: no se pudo inicializar el mapa.\n");
        return (1);
    }

    // Configurar la estructura de juego y MLX
    game.screen_width = SCREENWIDTH;
    game.screen_height = SCREENHEIGHT;
    game.player_pos_x = 1.5;
    game.player_pos_y = 1.5;
    game.player_dir_x = -1;
    game.player_dir_y = 0;
    game.plane_x = 0;
    game.plane_y = 0.66;

    mlx_t *mlx = mlx_init(game.screen_width, game.screen_height, "Cub3D", true);
    if (!mlx)
    {
        fprintf(stderr, "Error: no se pudo inicializar MLX42.\n");
        free_map(game.worldMap, mapHeight);
        return (1);
    }
    game.mlx = mlx;

    game.image = mlx_new_image(mlx, game.screen_width, game.screen_height);
    if (!game.image)
    {
        fprintf(stderr, "Error: no se pudo crear la imagen.\n");
        mlx_terminate(mlx);
        free_map(game.worldMap, mapHeight);
        return (1);
    }

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