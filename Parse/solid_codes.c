/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_codes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:47:49 by jeandrad          #+#    #+#             */
/*   Updated: 2025/02/06 15:18:59 by jeandrad         ###   ########.fr       */
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
	if (ft_strlen(str) > 3)
		return (0);
	if (ft_atoi(str) < 0 || ft_atoi(str) > 255)
		return (0);
	return (1);
}

// Function to check the values of the floor and ceiling
// it uses a pointer because of norminette
int	check_numbers(const char *str)
{
	int	num_count;
	int	value;

	num_count = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			value = 0;
			while (ft_isdigit(*str))
				value = value * 10 + (*str++ - '0');
			if (value < 0 || value > 255)
				return (0);
			num_count++;
		}
		else if (*str == ',')
			str++;
		else
			return (0);
	}
	return (num_count == 3);
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
	rgb_codes = p_calloc(3, sizeof(int));
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

// Function to get the hexadecimal codes for the floor and ceiling
void	get_hex_codes(t_game *game, t_element *element)
{
	int	*rgb_floor;
	int	*rgb_ceiling;

	rgb_floor = get_rgb_codes(element->floor);
	if (check_numbers(element->floor) == 0)
		ft_error("getting the color for the floor.\n", game);
	if (check_numbers(element->ceiling) == 0)
		ft_error("getting the color for the ceiling.\n", game);
	if (!rgb_floor)
		ft_error("Error getting the color for the floor.\n", game);
	game->floor = rgb_to_uint32(rgb_floor);
	free(rgb_floor);
	rgb_ceiling = get_rgb_codes(element->ceiling);
	if (!rgb_ceiling)
		ft_error("Error getting the color for the ceiling.\n", game);
	game->ceiling = rgb_to_uint32(rgb_ceiling);
	free(rgb_ceiling);
}
