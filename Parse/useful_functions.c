/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:54:39 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/28 19:49:53 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	free_map(char **map, int map_height)
{
	int	i;

	i = 0;
	while (i < map_height)
	{
		free(map[i]);
		i++;
	}
}

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
	if(game->world_map || game->map_height)
		free_map(game->world_map, game->map_height);
	if(game->mlx)
		mlx_terminate(game->mlx);
	if(game)
		free_textures(game);
	exit(1);
}

void	ft_error_mlx(const char *message, t_game *game)
{
	printf("Error: %s\n", message);
	mlx_terminate(game->mlx);
	free_map(game->world_map, game->map_height);
	free_textures(game);
	exit(1);
}
