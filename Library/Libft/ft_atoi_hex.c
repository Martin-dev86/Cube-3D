/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:48:43 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/24 11:53:59 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function to convert an RGB string to a uint32_t color value
uint32_t ft_atoi_base_hex(const char *rgb)
{
    int r = 0, g = 0, b = 0;
    int i = 0;

    while (rgb[i] != ',' && rgb[i] != '\0')
    {
        r = r * 10 + (rgb[i] - '0');
        i++;
    }
    i++; // Skip the comma

    while (rgb[i] != ',' && rgb[i] != '\0')
    {
        g = g * 10 + (rgb[i] - '0');
        i++;
    }
    i++; // Skip the comma

    while (rgb[i] != '\0')
    {
        b = b * 10 + (rgb[i] - '0');
        i++;
    }

    return (r << 16) | (g << 8) | b;
}
