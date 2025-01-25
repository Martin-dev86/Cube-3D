/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_codes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:47:49 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/25 16:00:04 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Function to check if a number is in the range of 0 to 255
int	check_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (ft_atoi(str) < 0 || ft_atoi(str) > 255)
		return (0);
	return (1);
}

// Function to convert an RGB string to an array of three integers
int	*get_rgb_codes(const char *rgb)
{
	int	*rgb_codes;
	int	i;
	int	j;
	int	value;

	i = 0;
	j = 0;
	value = 0;
	rgb_codes = malloc(3 * sizeof(int));
	if (!rgb_codes)
		return (NULL);
	while (rgb[i] != '\0' && j < 3)
	{
		if (rgb[i] >= '0' && rgb[i] <= '9')
			value = value * 10 + (rgb[i] - '0');
		else if (rgb[i] == ',')
		{
			rgb_codes[j++] = value;
			value = 0;
		}
		i++;
	}
	rgb_codes[j] = value;
	return (rgb_codes);
}

// Function to convert an array of three integers (RGB)
// to a uint32_t color value with alpha channel
uint32_t	rgb_to_uint32(int *rgb)
{
	uint32_t	color;

	color = 0;
	if (!rgb)
		return (0);
	color = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF;
	return (color);
}

void	get_hex_codes(t_game *game, t_element *element)
{
	int	*rgb_floor;
	int	*rgb_ceiling;

	rgb_floor = get_rgb_codes(element->floor);
	if (!rgb_floor)
	{
		printf("Error getting the color for the floor.\n");
		exit(EXIT_FAILURE);
	}
	game->floor = rgb_to_uint32(rgb_floor);
	free(rgb_floor);
	rgb_ceiling = get_rgb_codes(element->ceiling);
	if (!rgb_ceiling)
	{
		printf("Error getting the color for the ceiling.\n");
		exit(EXIT_FAILURE);
	}
	game->ceiling = rgb_to_uint32(rgb_ceiling);
	free(rgb_ceiling);
}
