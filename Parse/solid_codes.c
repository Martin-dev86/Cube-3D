/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_codes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:47:49 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/24 15:25:51 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Function to check is number and is in the range of 0 to 255
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
int *get_rgb_codes(const char *rgb)
{
    int *rgb_codes = malloc(3 * sizeof(int));
    int i = 0, j = 0, value = 0;

    if (!rgb_codes)
        return NULL;

    while (rgb[i] != '\0' && j < 3)
    {
        if (rgb[i] >= '0' && rgb[i] <= '9')
        {
            value = value * 10 + (rgb[i] - '0');
        }
        else if (rgb[i] == ',')
        {
            rgb_codes[j++] = value;
            value = 0;
        }
        i++;
    }
    rgb_codes[j] = value;

    return rgb_codes;
}

// Function to convert an array of three integers (RGB) to a uint32_t color value
uint32_t rgb_to_uint32(int *rgb)
{
    return (0xFF << 24) | (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}

void get_hex_codes(t_game *game, t_element *element)
{
    int *rgb_floor;
    int *rgb_ceiling;

    rgb_floor = get_rgb_codes(element->floor);
    printf("rgb floor done\n");
    if (!rgb_floor)
    {
        fprintf(stderr, "Error: no se pudo obtener los códigos RGB del piso.\n");
        exit(EXIT_FAILURE);
    }
    game->floor = rgb_to_uint32(rgb_floor);
    printf("rgb_floor REdone\n");
    free(rgb_floor);
    printf("rgb floor freed\n");
    printf("Floor: %s\n", element->floor);

    rgb_ceiling = get_rgb_codes(element->ceiling);
    printf("rgb ceiling done\n");
    if (!rgb_ceiling)
    {
        fprintf(stderr, "Error: no se pudo obtener los códigos RGB del techo.\n");
        exit(EXIT_FAILURE);
    }
    game->ceiling = rgb_to_uint32(rgb_ceiling);
    free(rgb_ceiling);
    printf("Ceiling: %s\n", element->ceiling);

    printf("Floor 0x%X\n", game->floor);
    printf("Ceiling 0x%X\n", game->ceiling);
    printf("rgb ceiling REdone\n");
}
