/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:25:23 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/14 15:45:08 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Function to clean the image
void	clear_image(mlx_image_t *image, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			mlx_put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}

// Function to draw a line
void	draw_line(t_game *game, uint32_t color, t_draw_line_params *params)
{
	int	y;

	y = params->start;
	while (y < params->end)
	{
		mlx_put_pixel(game->image, params->x, y, color);
		y++;
	}
}
