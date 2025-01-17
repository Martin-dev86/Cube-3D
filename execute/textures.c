/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:30:26 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/14 18:31:42 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Function to exit with and error message
void	error(const char *message, t_game *game)
{
	fprintf(stderr, "Error: %s\n", message);
	free_map(game->world_map, game->map_height);
	exit(1);
}

// Function to load the textures of the walls
// the format is xpm42 for better performance
void	load_walls(t_game *game)
{
	xpm_t	*xpm;

	xpm = mlx_load_xpm42("textures/neon_wall1.xpm42");
	if (!xpm)
		error("texture not found", game);
	game->textures.north = &xpm->texture;
	xpm = mlx_load_xpm42("textures/neon_wall2.xpm42");
	if (!xpm)
		error("texture not found", game);
	game->textures.south = &xpm->texture;
	xpm = mlx_load_xpm42("textures/neon_wall3.xpm42");
	if (!xpm)
		error("texture not found", game);
	game->textures.west = &xpm->texture;
	xpm = mlx_load_xpm42("textures/neon_broken_wall.xpm42");
	if (!xpm)
		error("texture not found", game);
	game->textures.east = &xpm->texture;
}
