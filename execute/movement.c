/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:27:00 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/11 12:02:35 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

bool is_impact(char **worldMap, double x, double y, int mapWidth, int mapHeight)
{
    (void)mapHeight;
    (void)mapWidth;
    // Verificar si las coordenadas están dentro de los límites del mapa
    // if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight)
    //     return true;

    // Verificar si hay un muro en las coordenadas considerando el radio del jugador
    if (worldMap[(int)y][(int)x] == '1')
        return true;

    return false;
}

void escape_key(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    if (keydata.key == MLX_KEY_ESCAPE)
    {
        mlx_close_window(game->mlx);
        //free_map(game->worldMap, game->mapHeight);
        exit(0);
    }
}

void foward_and_back_mov(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    double moveSpeed = MOVE_SPEED;
    int mapWidth = MAPWIDTH; // Asegúrate de definir MAPWIDTH
    int mapHeight = MAPHEIGHT; // Asegúrate de definir MAPHEIGHT

    if (keydata.key == MLX_KEY_W)
    {
        if (!is_impact(game->worldMap, game->player_pos_x + game->player_dir_x * moveSpeed, game->player_pos_y, mapWidth, mapHeight))
            game->player_pos_x += game->player_dir_x * moveSpeed;
        if (!is_impact(game->worldMap, game->player_pos_x, game->player_pos_y + game->player_dir_y * moveSpeed, mapWidth, mapHeight))
            game->player_pos_y += game->player_dir_y * moveSpeed;
    }
    if (keydata.key == MLX_KEY_S)
    {
        if (!is_impact(game->worldMap, game->player_pos_x - game->player_dir_x * moveSpeed, game->player_pos_y, mapWidth, mapHeight))
            game->player_pos_x -= game->player_dir_x * moveSpeed;
        if (!is_impact(game->worldMap, game->player_pos_x, game->player_pos_y - game->player_dir_y * moveSpeed, mapWidth, mapHeight))
            game->player_pos_y -= game->player_dir_y * moveSpeed;
    }
}

void side_mov(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    double moveSpeed = MOVE_SPEED;
    int mapWidth = MAPWIDTH; // Asegúrate de definir MAPWIDTH
    int mapHeight = MAPHEIGHT; // Asegúrate de definir MAPHEIGHT

    if (keydata.key == MLX_KEY_A)
    {
        if (!is_impact(game->worldMap, game->player_pos_x - game->plane_x * moveSpeed, game->player_pos_y, mapWidth, mapHeight))
            game->player_pos_x -= game->plane_x * moveSpeed;
        if (!is_impact(game->worldMap, game->player_pos_x, game->player_pos_y - game->plane_y * moveSpeed, mapWidth, mapHeight))
            game->player_pos_y -= game->plane_y * moveSpeed;
    }
    if (keydata.key == MLX_KEY_D)
    {
        if (!is_impact(game->worldMap, game->player_pos_x + game->plane_x * moveSpeed, game->player_pos_y, mapWidth, mapHeight))
            game->player_pos_x += game->plane_x * moveSpeed;
        if (!is_impact(game->worldMap, game->player_pos_x, game->player_pos_y + game->plane_y * moveSpeed, mapWidth, mapHeight))
            game->player_pos_y += game->plane_y * moveSpeed;
    }
}

void turn_mov(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    double rotSpeed = ROT_SPEED;

    if (keydata.key == MLX_KEY_RIGHT)
    {
        double oldDirX = game->player_dir_x;
        game->player_dir_x = game->player_dir_x * cos(-rotSpeed) - game->player_dir_y * sin(-rotSpeed);
        game->player_dir_y = oldDirX * sin(-rotSpeed) + game->player_dir_y * cos(-rotSpeed);
        double oldPlaneX = game->plane_x;
        game->plane_x = game->plane_x * cos(-rotSpeed) - game->plane_y * sin(-rotSpeed);
        game->plane_y = oldPlaneX * sin(-rotSpeed) + game->plane_y * cos(-rotSpeed);
    }
    if (keydata.key == MLX_KEY_LEFT)
    {
        double oldDirX = game->player_dir_x;
        game->player_dir_x = game->player_dir_x * cos(rotSpeed) - game->player_dir_y * sin(rotSpeed);
        game->player_dir_y = oldDirX * sin(rotSpeed) + game->player_dir_y * cos(rotSpeed);
        double oldPlaneX = game->plane_x;
        game->plane_x = game->plane_x * cos(rotSpeed) - game->plane_y * sin(rotSpeed);
        game->plane_y = oldPlaneX * sin(rotSpeed) + game->plane_y * cos(rotSpeed);
    }
}

// Función para mover al jugador
void move_player(mlx_key_data_t keydata, void *param)
{
    escape_key(keydata, param);
    foward_and_back_mov(keydata, param);
    side_mov(keydata, param);
    turn_mov(keydata, param);
}