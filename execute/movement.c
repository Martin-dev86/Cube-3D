/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:27:00 by jeandrad          #+#    #+#             */
/*   Updated: 2025/02/01 15:06:12 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Function to close the window with the ESC key
void	escape_key(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->mlx);
		free_w_map(game->world_map);
		exit(0);
	}
}

// Function to move the player backwards
// It also handles collisions with the walls
void	move_backward(t_game *game, double moveSpeed)
{
	if (game->world_map[(int)(game->pos_y - game->dir_y * moveSpeed
			+ PLAYER_RADIUS)][(int)(game->pos_x)] == '0'
		&& game->world_map[(int)(game->pos_y - game->dir_y * moveSpeed
			- PLAYER_RADIUS)][(int)(game->pos_x)] == '0'
		&& game->world_map[(int)(game->pos_y - game->dir_y
			* moveSpeed)][(int)(game->pos_x + PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y - game->dir_y
			* moveSpeed)][(int)(game->pos_x - PLAYER_RADIUS)] == '0')
	{
		game->pos_y -= game->dir_y * moveSpeed;
	}
	if (game->world_map[(int)(game->pos_y)][(int)(game->pos_x - game->dir_x
			* moveSpeed + PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y)][(int)(game->pos_x - game->dir_x
			* moveSpeed - PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y + PLAYER_RADIUS)][(int)(game->pos_x
			- game->dir_x * moveSpeed)] == '0'
		&& game->world_map[(int)(game->pos_y - PLAYER_RADIUS)][(int)(game->pos_x
			- game->dir_x * moveSpeed)] == '0')
	{
		game->pos_x -= game->dir_x * moveSpeed;
	}
}

// Function to move the player forward and backwards
void	foward_and_back_mov(void *param)
{
	t_game	*game;
	double	move_speed;

	game = (t_game *)param;
	move_speed = MOVE_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game, move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game, move_speed);
}

// Function to move the player
void	move_player(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		escape_key(keydata, param);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx,
			MLX_KEY_S))
		foward_and_back_mov(param);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A) || mlx_is_key_down(game->mlx,
			MLX_KEY_D))
		side_mov(param);
	turn_mov(param);
}
