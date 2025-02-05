/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_mov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:00:11 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/29 20:08:23 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Function to move the player to the right
// in the x axis
void	move_right_plane_x(t_game *game, double moveSpeed)
{
	if (game->world_map[(int)(game->pos_y)][(int)(game->pos_x + game->plane_x
			* moveSpeed + PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y)][(int)(game->pos_x + game->plane_x
			* moveSpeed - PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y + PLAYER_RADIUS)][(int)(game->pos_x
			+ game->plane_x * moveSpeed)] == '0'
		&& game->world_map[(int)(game->pos_y - PLAYER_RADIUS)][(int)(game->pos_x
			+ game->plane_x * moveSpeed)] == '0')
	{
		game->pos_x += game->plane_x * moveSpeed;
	}
}

// Function to move the player to the right
// in the y axis
void	move_right_plane_y(t_game *game, double moveSpeed)
{
	if (game->world_map[(int)(game->pos_y + game->plane_y * moveSpeed
			+ PLAYER_RADIUS)][(int)(game->pos_x)] == '0'
		&& game->world_map[(int)(game->pos_y + game->plane_y * moveSpeed
			- PLAYER_RADIUS)][(int)(game->pos_x)] == '0'
		&& game->world_map[(int)(game->pos_y + game->plane_y
			* moveSpeed)][(int)(game->pos_x + PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y + game->plane_y
			* moveSpeed)][(int)(game->pos_x - PLAYER_RADIUS)] == '0')
	{
		game->pos_y += game->plane_y * moveSpeed;
	}
}

// Function to move the player to the sides
void	side_mov(void *param)
{
	t_game	*game;
	double	move_speed;

	game = (t_game *)param;
	move_speed = MOVE_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		move_right_plane_x(game, -move_speed);
		move_right_plane_y(game, -move_speed);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		move_right_plane_x(game, move_speed);
		move_right_plane_y(game, move_speed);
	}
}
