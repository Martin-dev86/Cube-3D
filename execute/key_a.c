/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:15:23 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/14 15:38:54 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Aux function to move the player to the left
// in the X axis
void	move_left_plane_x(t_game *game, double moveSpeed)
{
	if (game->world_map[(int)(game->pos_y)][(int)(game->pos_x - game->plane_x
			* moveSpeed + PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y)][(int)(game->pos_x - game->plane_x
			* moveSpeed - PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y + PLAYER_RADIUS)][(int)(game->pos_x
			- game->plane_x * moveSpeed)] == '0'
		&& game->world_map[(int)(game->pos_y - PLAYER_RADIUS)][(int)(game->pos_x
			- game->plane_x * moveSpeed)] == '0')
	{
		game->pos_x -= game->plane_x * moveSpeed;
	}
}

// Aux function to move the player to the left
// in the Y axis
void	move_left_plane_y(t_game *game, double moveSpeed)
{
	if (game->world_map[(int)(game->pos_y - game->plane_y * moveSpeed
			+ PLAYER_RADIUS)][(int)(game->pos_x)] == '0'
		&& game->world_map[(int)(game->pos_y - game->plane_y * moveSpeed
			- PLAYER_RADIUS)][(int)(game->pos_x)] == '0'
		&& game->world_map[(int)(game->pos_y - game->plane_y
			* moveSpeed)][(int)(game->pos_x + PLAYER_RADIUS)] == '0'
		&& game->world_map[(int)(game->pos_y - game->plane_y
			* moveSpeed)][(int)(game->pos_x - PLAYER_RADIUS)] == '0')
	{
		game->pos_y -= game->plane_y * moveSpeed;
	}
}

// Function to move the player to the left
void	key_a(mlx_key_data_t keydata, void *param)
{
	double	move_speed;
	t_game	*game;

	move_speed = MOVE_SPEED;
	game = (t_game *)param;
	if (keydata.key == MLX_KEY_A)
	{
		move_left_plane_x(game, move_speed);
		move_left_plane_y(game, move_speed);
	}
}
