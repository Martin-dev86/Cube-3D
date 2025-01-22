/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:30:26 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/22 19:34:55 by cagarci2         ###   ########.fr       */
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
void	load_walls(t_game *game, t_element *elem)
{
	xpm_t	*xpm;

	xpm = mlx_load_xpm42(elem->north);
	if (!xpm)
		error("texture not found1", game);
	game->textures.north = &xpm->texture;
	printf("Texture north loaded\n");
	xpm = mlx_load_xpm42(elem->south);
	printf("Texture south xmp42 succcess\n");
	if (!xpm)
		error("texture not found2", game);
	game->textures.south = &xpm->texture;
	printf("Texture south loaded\n");
	xpm = mlx_load_xpm42(elem->west);
	if (!xpm)
		error("texture not found3", game);
	game->textures.west = &xpm->texture;
	xpm = mlx_load_xpm42(elem->east);
	printf("Texture east loaded\n");
	if (!xpm)
		error("texture not found4", game);
	game->textures.east = &xpm->texture;
	printf("Textures loaded\n");
}
