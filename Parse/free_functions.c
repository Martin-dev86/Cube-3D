/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:35:14 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/29 20:36:17 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	free_map(char **map, int map_height)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < map_height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_w_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
