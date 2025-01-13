/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:25:23 by jeandrad          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/01/13 18:46:02 by jeandrad         ###   ########.fr       */
=======
/*   Updated: 2024/12/20 18:02:10 by jeandrad         ###   ########.fr       */
>>>>>>> dbc6ffb (now the hardcoded game without textures works)
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

<<<<<<< HEAD
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
void	draw_line(t_game *game, int x, int start, int end, uint32_t color)
=======
// Función para limpiar la pantalla
void clear_image(mlx_image_t *image, uint32_t color)
{
    int x;
    int y;

    y = 0;
    x = 0;
    while (y < SCREENHEIGHT)
    {
        x = 0;
        while  (x < SCREENWIDTH)
        {
            mlx_put_pixel(image, x, y, color);
            x++;
        }
        y++;
    }
}

// Función para dibujar una línea
void draw_line(t_game *game, int x, int start, int end, uint32_t color)
>>>>>>> dbc6ffb (now the hardcoded game without textures works)
{
	int	y;

<<<<<<< HEAD
	y = start;
	while (y < end)
	{
		mlx_put_pixel(game->image, x, y, color);
		y++;
	}
=======
    y = start;
    while (y < end)
    {
        mlx_put_pixel(game->image, x, y, color);
        y++;
    }
>>>>>>> dbc6ffb (now the hardcoded game without textures works)
}

