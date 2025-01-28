/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:50:08 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/28 14:52:42 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	get_map_size(t_game *game)
{
	int	i;

	i = 0;
	game->map_height = 0;
	while (game->world_map[i])
	{
		game->map_height++;
		i++;
	}
}

void	get_map_width(t_game *game)
{
	int	i;
	int	j;
	int	width;
	int	m_width;

	i = 0;
	width = 0;
	m_width = 0;
	while (game->world_map[i])
	{
		j = 0;
		while (game->world_map[i][j])
		{
			width++;
			j++;
		}
		if (width > m_width)
		{
			m_width = width;
			game->map_width = width;
		}
		width = 0;
		i++;
	}
}

void	create_map(t_game *game)
{
	int	i;
	int	j;

	get_map_size(game);
	get_map_width(game);
	game->map = ft_calloc(game->map_height, sizeof(char *));
	if (!game->map)
	{
		printf("Error: Memory allocation failed for world_map.\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < game->map_height; i++)
	{
		game->map[i] = ft_calloc(game->map_width, sizeof(char));   
		if (!game->map[i])
		{
			printf("Error: Memory allocation failed for world_map[%d].\n", i);
			for (int k = 0; k < i; k++)
				free(game->world_map[k]);
			free(game->world_map);
			exit(EXIT_FAILURE);
		}
	}
	i = 6;
	while (game->world_map[i])
	{
		j = 0;
		while (game->world_map[i][j])
		{
			game->map[i - 6][j] = game->world_map[i][j];
			j++;
		}
		i++;
	}
}
