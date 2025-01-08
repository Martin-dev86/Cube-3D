/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:26:30 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/08 20:03:51 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Dibuja un píxel en la pantalla
void put_pixel_to_image(mlx_image_t *image, int x, int y, int color)
{
    if (x >= 0 && x < (int)image->width && y >= 0 && y < (int)image->height) {
        int index = (y * image->width + x) * 4; // Asumiendo 4 canales (RGBA)
        image->pixels[index + 0] = (color >> 0) & 0xFF;  // Canal azul
        image->pixels[index + 1] = (color >> 8) & 0xFF;  // Canal verde
        image->pixels[index + 2] = (color >> 16) & 0xFF; // Canal rojo
        image->pixels[index + 3] = (color >> 24) & 0xFF; // Canal alfa
    }
}

void render_floor_and_ceiling(t_game *game)
{
    // Pintar el cielo de azul
    for (int y = 0; y < game->screen_height / 2; y++)
    {
        for (int x = 0; x < game->screen_width; x++)
        {
            put_pixel_to_image(game->image, x, y, 0x0000FF); // Azul
        }
    }

    // Pintar el suelo de negro
    for (int y = game->screen_height / 2; y < game->screen_height; y++)
    {
        for (int x = 0; x < game->screen_width; x++)
        {
            put_pixel_to_image(game->image, x, y, 0x000000); // Negro
        }
    }
}
// Obtiene el color de un píxel en la textura
int get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
    int index = (y * texture->width + x) * 4; // Asumiendo 4 canales (RGBA)
    return *(int *)&texture->pixels[index];
}

// Dibuja un píxel en la pantalla

#include "../Includes/cub3d.h"

void render_walls(void *param)
{
    t_game *game = (t_game *)param;

    // Pintar el suelo y el cielo
    render_floor_and_ceiling(game);

    for (int x = 0; x < game->screen_width; x++) {
        // Calcular la posición y dirección del rayo
        double camera_x = 2 * x / (double)game->screen_width - 1;
        double ray_dir_x = game->player_dir_x + game->plane_x * camera_x;
        double ray_dir_y = game->player_dir_y + game->plane_y * camera_x;

        // Posición actual del jugador en el mapa
        int map_x = (int)game->player_pos_x;
        int map_y = (int)game->player_pos_y;

        // Distancia a los lados de las celdas
        double side_dist_x;
        double side_dist_y;

        // Longitudes de los rayos desde una celda a la siguiente
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        double perp_wall_dist;

        // Dirección de desplazamiento y verificación del paso
        int step_x;
        int step_y;
        int hit = 0;
        int side;

        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (game->player_pos_x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->player_pos_x) * delta_dist_x;
        }

        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (game->player_pos_y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->player_pos_y) * delta_dist_y;
        }

        // Realiza el DDA
        while (!hit) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }

            // Aquí verifica si el rayo ha golpeado una pared (1 en el mapa)
            if (game->worldMap[map_x][map_y] == '1') {
                hit = 1;
            }
        }

        // Calcula la distancia perpendicular a la pared
        if (side == 0) {
            perp_wall_dist = (map_x - game->player_pos_x + (1 - step_x) / 2) / ray_dir_x;
        } else {
            perp_wall_dist = (map_y - game->player_pos_y + (1 - step_y) / 2) / ray_dir_y;
        }

        // Calcula la altura de la línea para dibujar en la pantalla
        int line_height = (int)(game->screen_height / perp_wall_dist);

        // Calcula el inicio y fin de la línea en la pantalla
        int draw_start = -line_height / 2 + game->screen_height / 2;
        if (draw_start < 0) draw_start = 0;

        int draw_end = line_height / 2 + game->screen_height / 2;
        if (draw_end >= game->screen_height) draw_end = game->screen_height - 1;

        // Selecciona la textura según el lado de la pared
        mlx_texture_t *texture;
        if (side == 0 && ray_dir_x > 0)
            texture = game->textures.east;
        else if (side == 0 && ray_dir_x < 0)
            texture = game->textures.west;
        else if (side == 1 && ray_dir_y > 0)
            texture = game->textures.south;
        else
            texture = game->textures.north;

        // Calcula la coordenada x en la textura
        double wall_x;
        if (side == 0)
            wall_x = game->player_pos_y + perp_wall_dist * ray_dir_y;
        else
            wall_x = game->player_pos_x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);

        int tex_x = (int)(wall_x * (double)texture->width);
        if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
            tex_x = texture->width - tex_x - 1;

        // Dibuja la pared vertical línea por línea
        double step = 1.0 * texture->height / line_height;
        double tex_pos = (draw_start - game->screen_height / 2 + line_height / 2) * step;

        for (int y = draw_start; y < draw_end; y++) {
            int tex_y = (int)tex_pos & (texture->height - 1);
            tex_pos += step;
            int color = get_texture_pixel(texture, tex_x, tex_y);
            put_pixel_to_image(game->image, x, y, color);
        }
    }
    mlx_image_to_window(game->mlx, game->image, 0, 0);
}
