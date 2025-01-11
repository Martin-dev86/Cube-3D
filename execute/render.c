/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:26:30 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/11 11:56:14 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

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

// minimapa
void draw_mini(t_game *game)
{
    int mini_map_scale = 20; // Escala del minimapa
    int mini_map_size = 40; // Tamaño del minimapa en celdas

    for (int y = 0; y < mini_map_size; y++) {
        for (int x = 0; x < mini_map_size; x++) {
            int map_x = (int)game->player_pos_x - mini_map_size / 2 + x;
            int map_y = (int)game->player_pos_y - mini_map_size / 2 + y;

            if (map_x >= 0 && map_x < MAPWIDTH && map_y >= 0 && map_y < MAPHEIGHT) {
                int color = (game->worldMap[map_y][map_x] == '1') ? 0xFFFFFF : 0x000000; // Blanco para muros, negro para espacios vacíos
                if (map_x == (int)game->player_pos_x && map_y == (int)game->player_pos_y)
                    color = 0xFF0000; // Rojo para el jugador

                for (int i = 0; i < mini_map_scale; i++) {
                    for (int j = 0; j < mini_map_scale; j++) {
                        put_pixel_to_image(game->image, x * mini_map_scale + i, y * mini_map_scale + j, color);
                    }
                }
            }
        }
    }
}

void check_collisions(t_game *game)
{
    int player_x = (int)game->player_pos_x;
    int player_y = (int)game->player_pos_y;

    if (game->worldMap[player_y][player_x] == '1')
    {
        printf("Collision detected at (%d, %d)\n", player_x, player_y);
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

void calculate_ray_position_and_direction(t_game *game, int x, double *camera_x, double *ray_dir_x, double *ray_dir_y)
{
    *camera_x = 2 * x / (double)game->screen_width - 1;
    *ray_dir_x = game->player_dir_x + game->plane_x * (*camera_x);
    *ray_dir_y = game->player_dir_y + game->plane_y * (*camera_x);
}

void perform_dda(t_game *game, double ray_dir_x, double ray_dir_y, int *map_x, int *map_y, double *side_dist_x, double *side_dist_y, double delta_dist_x, double delta_dist_y, int *step_x, int *step_y, int *side, double *perp_wall_dist)
{
    int hit = 0;

    if (ray_dir_x < 0) {
        *step_x = -1;
        *side_dist_x = (game->player_pos_x - *map_x) * delta_dist_x;
    } else {
        *step_x = 1;
        *side_dist_x = (*map_x + 1.0 - game->player_pos_x) * delta_dist_x;
    }

    if (ray_dir_y < 0) {
        *step_y = -1;
        *side_dist_y = (game->player_pos_y - *map_y) * delta_dist_y;
    } else {
        *step_y = 1;
        *side_dist_y = (*map_y + 1.0 - game->player_pos_y) * delta_dist_y;
    }

    while (!hit) {
        if (*side_dist_x < *side_dist_y) {
            *side_dist_x += delta_dist_x;
            *map_x += *step_x;
            *side = 0;
        } else {
            *side_dist_y += delta_dist_y;
            *map_y += *step_y;
            *side = 1;
        }

        if (game->worldMap[*map_x][*map_y] == '1') {
            hit = 1;
        }
    }

    if (*side == 0) {
        *perp_wall_dist = (*map_x - game->player_pos_x + (1 - *step_x) / 2) / ray_dir_x;
    } else {
        *perp_wall_dist = (*map_y - game->player_pos_y + (1 - *step_y) / 2) / ray_dir_y;
    }
}

void draw_wall(t_game *game, int x, int side, double perp_wall_dist, double ray_dir_x, double ray_dir_y)
{
    int line_height = (int)(game->screen_height / perp_wall_dist);

    int draw_start = -line_height / 2 + game->screen_height / 2;
    if (draw_start < 0) draw_start = 0;

    int draw_end = line_height / 2 + game->screen_height / 2;
    if (draw_end >= game->screen_height) draw_end = game->screen_height - 1;

    mlx_texture_t *texture;
    if (side == 0 && ray_dir_x > 0)
        texture = game->textures.east;
    else if (side == 0 && ray_dir_x < 0)
        texture = game->textures.west;
    else if (side == 1 && ray_dir_y > 0)
        texture = game->textures.south;
    else
        texture = game->textures.north;

    double wall_x;
    if (side == 0)
        wall_x = game->player_pos_y + perp_wall_dist * ray_dir_y;
    else
        wall_x = game->player_pos_x + perp_wall_dist * ray_dir_x;
    wall_x -= floor(wall_x);

    int tex_x = (int)(wall_x * (double)texture->width);
    if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
        tex_x = texture->width - tex_x - 1;

    double step = 1.0 * texture->height / line_height;
    double tex_pos = (draw_start - game->screen_height / 2 + line_height / 2) * step;

    for (int y = draw_start; y < draw_end; y++) {
        int tex_y = (int)tex_pos & (texture->height - 1);
        tex_pos += step;
        int color = get_texture_pixel(texture, tex_x, tex_y);
        put_pixel_to_image(game->image, x, y, color);
    }
}

void render_walls(void *param)
{
    t_game *game = (t_game *)param;

    render_floor_and_ceiling(game);

    for (int x = 0; x < game->screen_width; x++) {
        double camera_x, ray_dir_x, ray_dir_y;
        calculate_ray_position_and_direction(game, x, &camera_x, &ray_dir_x, &ray_dir_y);

        int map_x = (int)game->player_pos_x;
        int map_y = (int)game->player_pos_y;
        double side_dist_x, side_dist_y;
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        int step_x, step_y, side;
        double perp_wall_dist;

        perform_dda(game, ray_dir_x, ray_dir_y, &map_x, &map_y, &side_dist_x, &side_dist_y, delta_dist_x, delta_dist_y, &step_x, &step_y, &side, &perp_wall_dist);

        draw_wall(game, x, side, perp_wall_dist, ray_dir_x, ray_dir_y);
    }
    //draw_mini(game); // Llamada a la función para dibujar el minimapa
    check_collisions(game);
    mlx_image_to_window(game->mlx, game->image, 0, 0);
}
