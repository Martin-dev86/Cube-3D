/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:54:39 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/29 20:35:27 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Protected calloc function
void	*p_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		printf("Error: Memory allocation failed.\n");
		exit(1);
	}
	return (ptr);
}

// Function to exit with and error message
void	ft_error(const char *message, t_game *game)
{
	printf("Error: %s\n", message);
	if (game->world_map || game->map_height)
		free_w_map(game->world_map);
	if (game->mlx)
		mlx_terminate(game->mlx);
	if (game)
		free_textures(game);
	exit(1);
}

void	ft_error_mlx(const char *message, t_game *game)
{
	printf("Error: %s\n", message);
	mlx_terminate(game->mlx);
	free_w_map(game->world_map);
	free_map(game->map, game->map_height);
	free_textures(game);
	exit(1);
}

void	free_element(t_element *element)
{
	if (element == NULL)
		return ;
	if (element->north)
		free(element->north);
	if (element->south)
		free(element->south);
	if (element->west)
		free(element->west);
	if (element->east)
		free(element->east);
	if (element->floor)
		free(element->floor);
	if (element->ceiling)
		free(element->ceiling);
}
