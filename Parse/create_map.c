/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:50:08 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/21 18:16:23 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"
void get_map_size(t_game *game)
{
    int i;

    i = 0;
    game->map_height = 0;
    while (game->world_map[i])
    {
        game->map_height++;
        i++;
    }
}

void get_map_width(t_game *game)
{
    int i;
    int j;
    int width;
    int m_width;

    i = 0;
    width = 0;
    m_width = 0;
    while(game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            width++;
            j++;
        }
        if (width > m_width)
        {
            m_width = width;
            game->map_width = width;
        }
        width = 0;
        i++;
    }
}

void create_map(t_game *game)
{
    int i;
    int j;

    // Asegúrate de que game->map no sea NULL
    if (!game->map)
    {
        printf("Error: game->map is NULL\n");
        return;
    }

    // Inicializa game->world_map con el tamaño adecuado
    game->world_map = malloc(game->map_height * sizeof(char *));
    for (i = 0; i < game->map_height; i++)
    {
        game->world_map[i] = malloc(game->map_width * sizeof(char));
    }

    i = 0;
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            game->world_map[i][j] = game->map[i][j];
            j++;
        }
        i++;
    }
    printf("Map created\n");
    get_map_size(game);
    printf("Map size got %d\n", game->map_height);
    get_map_width(game);
    printf("Map width got %d\n", game->map_width);
}
