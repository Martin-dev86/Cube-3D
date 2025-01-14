/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:41:03 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/14 17:43:37 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	free_textures(t_game *game)
{
	mlx_delete_texture(game->textures.north);
    mlx_delete_texture(game->textures.south);
    mlx_delete_texture(game->textures.west);
    mlx_delete_texture(game->textures.east);
}
