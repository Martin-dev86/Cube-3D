/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_celiling_codes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:47:49 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/22 19:02:53 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

// Function to check is number and is in the range of 0 to 255
int check_number(char *str)
{
    int i;

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

// to get the 3 numbers from the string of floor and ceiling
int *get_rgb_codes(t_element *elem)
{
    int *n;
    int i;

    n = malloc(sizeof(int) * 3);
    if (!n)
        return (NULL);
    i = 0;
    while (elem->floor[i])
    {
        if (elem->floor[i] == ',')
            elem->floor[i] = ' ';
        i++;
    }
    return (n);
}

// Function to transform the rgb codes to a single 