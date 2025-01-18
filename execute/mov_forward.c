/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_forward.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:56:43 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/14 16:07:41 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Function to move the player forward in the y axis
void	move_forward_y(t_game *game, double moveSpeed)
{
	if (game->world_map[(int)(game->pos_y + game->dir_y * moveSpeed
			+ PLAYER_RADIUS)][(int)(game->pos_x)] == '0'
		&& game->world_map[(int)(game->pos_y + game->dir_y * moveSpeed
			- PLAYER_RADIUS)][(int)(game->pos_x)] == '0'
		&& game->world_map[(int)(game->pos_y + game->dir_y
			* moveSpeed)][(int)(game->pos_x + PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y + game->dir_y
			* moveSpeed)][(int)(game->pos_x - PLAYER_RADIUS)] == '0')
	{
		game->pos_y += game->dir_y * moveSpeed;
	}
}

// Function to move the player forward in the x axis
void	move_forward_x(t_game *game, double moveSpeed)
{
	if (game->world_map[(int)(game->pos_y)][(int)(game->pos_x + game->dir_x
			* moveSpeed + PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y)][(int)(game->pos_x + game->dir_x
			* moveSpeed - PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y + PLAYER_RADIUS)][(int)(game->pos_x
			+ game->dir_x * moveSpeed)] == '0'
		&& game->world_map[(int)(game->pos_y - PLAYER_RADIUS)][(int)(game->pos_x
			+ game->dir_x * moveSpeed)] == '0')
	{
		game->pos_x += game->dir_x * moveSpeed;
	}
}

// Function to move the player forward with the key W
void	key_w(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	double	move_speed;

	game = (t_game *)param;
	move_speed = MOVE_SPEED;
	if (keydata.key == MLX_KEY_W)
	{
		move_forward_y(game, move_speed);
		move_forward_x(game, move_speed);
	}
}

// Function to move the player forward
// It also handles the collision with the walls
void	move_forward(t_game *game, double moveSpeed)
{
	if (game->world_map[(int)(game->pos_y + game->dir_y * moveSpeed
			+ PLAYER_RADIUS)][(int)(game->pos_x)] == '0'
		&& game->world_map[(int)(game->pos_y + game->dir_y * moveSpeed
			- PLAYER_RADIUS)][(int)(game->pos_x)] == '0'
		&& game->world_map[(int)(game->pos_y + game->dir_y
			* moveSpeed)][(int)(game->pos_x + PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y + game->dir_y
			* moveSpeed)][(int)(game->pos_x - PLAYER_RADIUS)] == '0')
	{
		game->pos_y += game->dir_y * moveSpeed;
	}
	if (game->world_map[(int)(game->pos_y)][(int)(game->pos_x + game->dir_x
			* moveSpeed + PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y)][(int)(game->pos_x + game->dir_x
			* moveSpeed - PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y + PLAYER_RADIUS)][(int)(game->pos_x
			+ game->dir_x * moveSpeed)] == '0'
		&& game->world_map[(int)(game->pos_y - PLAYER_RADIUS)][(int)(game->pos_x
			+ game->dir_x * moveSpeed)] == '0')
	{
		game->pos_x += game->dir_x * moveSpeed;
	}
}
