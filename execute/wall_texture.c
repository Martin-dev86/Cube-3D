/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:24:37 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/14 16:13:28 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Function to get the texture of the wall
// It returns the texture depending on the orientation of the wall
mlx_texture_t	*get_texture(t_game *game, t_ray *ray, t_lines *lines)
{
	if (lines->side == 0 && ray->raydir_x > 0)
		return (game->textures.east);
	else if (lines->side == 0 && ray->raydir_x < 0)
		return (game->textures.west);
	else if (lines->side == 1 && ray->raydir_y > 0)
		return (game->textures.south);
	else
		return (game->textures.north);
}

// Function to calculate the x coordinate of the wall
double	calculate_wall_x(t_game *game, t_ray *ray, t_lines *lines)
{
	if (lines->side == 0)
		return (game->pos_y + ray->perpwalldist * ray->raydir_y);
	else
		return (game->pos_x + ray->perpwalldist * ray->raydir_x);
}

// Function to draw the wall with the texture
// It calculates the texture x and y coordinates
// and draws the wall with the texture
void	draw_wall_with_texture(t_game *game, t_ray *ray, int x, t_lines *lines)
{
	int		y;
	int		d;
	uint8_t	*pixel;

	game->texture = get_texture(game, ray, lines);
	lines->wall_x = calculate_wall_x(game, ray, lines);
	lines->wall_x -= floor(lines->wall_x);
	lines->tex_x = (int)(lines->wall_x * (double)game->texture->width);
	if ((lines->side == 0 && ray->raydir_x > 0) || (lines->side == 1
			&& ray->raydir_y < 0))
		lines->tex_x = game->texture->width - lines->tex_x - 1;
	y = lines->drawstart;
	while (y < lines->drawend)
	{
		d = y * 256 - SCREENHEIGHT * 128 + lines->lineheight * 128;
		lines->tex_y = ((d * game->texture->height) / lines->lineheight) / 256;
		pixel = game->texture->pixels + (lines->tex_y * game->texture->width
				+ lines->tex_x) * 4;
		game->color = (pixel[0] << 24) | (pixel[1] << 16) \
		| (pixel[2] << 8) | pixel[3];
		mlx_put_pixel(game->image, x, y, game->color);
		y++;
	}
}
