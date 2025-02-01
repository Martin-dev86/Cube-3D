/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:30:26 by jeandrad          #+#    #+#             */
/*   Updated: 2025/02/01 18:58:23 by jeandrad         ###   ########.fr       */
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
		ft_error("texture north not found", game);
	game->textures.north = &xpm->texture;
	xpm = mlx_load_xpm42(elem->south);
	if (!xpm)
		ft_error("texture south not found", game);
	game->textures.south = &xpm->texture;
	xpm = mlx_load_xpm42(elem->west);
	if (!xpm)
		ft_error("texture west not found", game);
	game->textures.west = &xpm->texture;
	xpm = mlx_load_xpm42(elem->east);
	if (!xpm)
		ft_error("texture east not found", game);
	game->textures.east = &xpm->texture;
}
