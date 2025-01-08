/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:23:11 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/08 18:14:43 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d.h"

void	free_map(char **map, int mapHeight)
{
    for (int i = 0; i < mapHeight; i++)
        free(map[i]);
    free(map);
}

char	**initialize_map(const char *mapData[], int mapHeight)
{
    char	**map;

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

int	main(void)
{
    t_game		game;
    const char	*mapData[] = {
        "11111111",
        "10010001",
        "10010101",
        "1000100111",
        "10000001 1",
        "1111111111",
        "10000001",
        "11111111",
        "",
        "11111111",
        "10000001",
        "11111111"
    };
    int			mapHeight;
    int			mapWidth;

    // Datos iniciales del mapa
    mapHeight = sizeof(mapData) / sizeof(mapData[0]);
    mapWidth = strlen(mapData[0]);
    game.mapHeight = mapHeight;
    game.mapWidth = mapWidth;
    game.worldMap = initialize_map(mapData, mapHeight);
    if (!game.worldMap)
    {
        fprintf(stderr, "Error: no se pudo inicializar el mapa.\n");
        return (1);
    }
    printf("Mapa inicializado correctamente.\n");
    game.mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Cub3D", true);
    if (!game.mlx)
    {
        fprintf(stderr, "Error: no se pudo inicializar MLX42.\n");
        free_map(game.worldMap, mapHeight);
        return (1);
    }
    printf("MLX42 inicializado correctamente.\n");
    game.image = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
    if (!game.image)
    {
        fprintf(stderr, "Error: no se pudo crear la imagen.\n");
        mlx_terminate(game.mlx);
        free_map(game.worldMap, mapHeight);
        return (1);
    }
    // Posición inicial del jugador
    game.posX = 1.5;
    game.posY = 1.5;
    game.dirX = -1;
    game.dirY = 0;
    game.planeX = 0;
    game.planeY = 0.66;

    // Cargar texturas
    load_walls(&game);

    printf("Jugador inicializado correctamente.\n");
    mlx_loop_hook(game.mlx, &update_and_render, &game);
    printf("Bucle principal iniciado.\n");
    mlx_key_hook(game.mlx, &move_player, &game);
    printf("Movimiento del jugador habilitado.\n");
    mlx_loop(game.mlx);
    printf("MLX42 terminado.\n");
    // Liberar recursos
    free_map(game.worldMap, mapHeight);
    printf("Mapa liberado.\n");
    mlx_terminate(game.mlx);
    return (0);
}
