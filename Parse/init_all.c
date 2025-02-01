/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:52:17 by jeandrad          #+#    #+#             */
/*   Updated: 2025/02/01 18:52:26 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

static void	init_textures(t_game *game)
{
	game->texture = NULL;
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.west = NULL;
	game->textures.east = NULL;
}

static void	initialize_game(t_game *game)
{
	game->ceiling = 0;
	game->color = 0;
	game->dir_x = 0;
	game->dir_y = 0;
	game->element.ceiling = NULL;
	game->element.east = NULL;
	game->element.floor = NULL;
	game->element.north = NULL;
	game->element.south = NULL;
	game->element.west = NULL;
	game->file_size = 0;
	game->floor = 0;
	game->image = NULL;
	game->initial_orientation = 0;
	game->map = NULL;
	game->map_height = 0;
	game->map_width = 0;
	game->mlx = NULL;
	game->pos_x = 0;
	game->pos_y = 0;
	game->read_cont = 0;
	game->world_map = NULL;
	init_textures(game);
}

static void	init_elem(t_element *element)
{
	element->ceiling = NULL;
	element->east = NULL;
	element->floor = NULL;
	element->north = NULL;
	element->south = NULL;
	element->west = NULL;
}

void	init_all(t_game *game, t_element *element)
{
	initialize_game(game);
	init_elem(element);
}
