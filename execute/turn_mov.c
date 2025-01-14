/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_mov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:58:52 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/14 15:31:02 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	turn_left(t_game *game, double rotSpeed)
{
	t_old	old;

	old.dir_x = game->dir_x;
	old.plane_x = game->plane_x;
	game->dir_x = game->dir_x * cos(-rotSpeed) - game->dir_y * sin(-rotSpeed);
	game->dir_y = old.dir_x * sin(-rotSpeed) + game->dir_y * cos(-rotSpeed);
	game->plane_x = game->plane_x * cos(-rotSpeed) - game->plane_y
		* sin(-rotSpeed);
	game->plane_y = old.plane_x * sin(-rotSpeed) + game->plane_y
		* cos(-rotSpeed);
}

void	turn_right(t_game *game, double rotSpeed)
{
	t_old	old;

	old.dir_x = game->dir_x;
	old.plane_x = game->plane_x;
	game->dir_x = game->dir_x * cos(rotSpeed) - game->dir_y * sin(rotSpeed);
	game->dir_y = old.dir_x * sin(rotSpeed) + game->dir_y * cos(rotSpeed);
	game->plane_x = game->plane_x * cos(rotSpeed) - game->plane_y
		* sin(rotSpeed);
	game->plane_y = old.plane_x * sin(rotSpeed) + game->plane_y * cos(rotSpeed);
}

void	turn_mov(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	double	rot_speed;

	game = (t_game *)param;
	rot_speed = ROT_SPEED;
	if (keydata.key == MLX_KEY_LEFT)
		turn_left(game, rot_speed);
	if (keydata.key == MLX_KEY_RIGHT)
		turn_right(game, rot_speed);
}
