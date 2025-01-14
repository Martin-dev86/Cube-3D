/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:26:30 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/14 16:10:51 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Function to calculate the y coordinate of the ray
void	ray_y(t_game game, t_ray *ray)
{
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (game.pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - game.pos_y) * ray->deltadist_y;
	}
}

// Function to perform the DDA algorithm
// The digital differential analyzer algorithm is used to calculate the distance
// of the player with the walls
void	dda_function(t_ray *ray, t_game *game, int *hit, int *side)
{
	while (*hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			*side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			*side = 1;
		}
		if (game->world_map[ray->map_y][ray->map_x] > '0')
			*hit = 1;
	}
	if (*side == 0)
		ray->perpwalldist = (ray->map_x - game->pos_x + (1 - ray->step_x) / 2)
			/ ray->raydir_x;
	else
		ray->perpwalldist = (ray->map_y - game->pos_y + (1 - ray->step_y) / 2)
			/ ray->raydir_y;
}

// Function to initialize the ray
// It gives the initial values to the ray
void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)SCREENWIDTH - 1;
	ray->raydir_x = game->dir_x + game->plane_x * ray->camera_x;
	ray->raydir_y = game->dir_y + game->plane_y * ray->camera_x;
	ray->map_x = (int)game->pos_x;
	ray->map_y = (int)game->pos_y;
	ray->deltadist_x = fabs(1 / ray->raydir_x);
	ray->deltadist_y = fabs(1 / ray->raydir_y);
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (game->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - game->pos_x) * ray->deltadist_x;
	}
	ray_y(*game, ray);
}

// Function to draw the floor and the ceiling
// Solid color for the floor and the ceiling
void	draw_floor_and_ceiling(t_game *game, int x)
{
	t_draw_line_params	params;

	params.x = x;
	params.start = 0;
	params.end = SCREENHEIGHT / 2;
	draw_line(game, 0x87CEEBFF, &params);
	params.start = SCREENHEIGHT / 2;
	params.end = SCREENHEIGHT;
	draw_line(game, 0x228B22FF, &params);
}

// Main function to render the game
// It updates where the player is looking and 
// renders floor, ceiling and the walls
void	update_and_render(void *param)
{
	t_lines	lines;
	t_game	*game;
	t_ray	ray;

	lines.x = 0;
	game = (t_game *)param;
	clear_image(game->image, 0x000000FF);
	while (lines.x < SCREENWIDTH)
	{
		draw_floor_and_ceiling(game, lines.x);
		init_ray(&ray, game, lines.x);
		lines.hit = 0;
		dda_function(&ray, game, &lines.hit, &lines.side);
		lines.lineheight = (int)(SCREENHEIGHT / ray.perpwalldist);
		lines.drawstart = -lines.lineheight / 2 + SCREENHEIGHT / 2;
		if (lines.drawstart < 0)
			lines.drawstart = 0;
		lines.drawend = lines.lineheight / 2 + SCREENHEIGHT / 2;
		if (lines.drawend >= SCREENHEIGHT)
			lines.drawend = SCREENHEIGHT - 1;
		draw_wall_with_texture(game, &ray, lines.x, &lines);
		lines.x++;
	}
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}
