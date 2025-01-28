/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:30:26 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/28 15:36:14 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Function to load the textures of the walls
// the format is xpm42 for better performance
void	load_walls(t_game *game, t_element *elem)
{
	xpm_t	*xpm;

	xpm = mlx_load_xpm42(elem->north);
	if (!xpm)
		ft_error("texture not found1", game);
	game->textures.north = &xpm->texture;
	xpm = mlx_load_xpm42(elem->south);
	if (!xpm)
		ft_error("texture not found2", game);
	game->textures.south = &xpm->texture;
	xpm = mlx_load_xpm42(elem->west);
	if (!xpm)
		ft_error("texture not found3", game);
	game->textures.west = &xpm->texture;
	xpm = mlx_load_xpm42(elem->east);
	if (!xpm)
		ft_error("texture not found4", game);
	game->textures.east = &xpm->texture;
}
