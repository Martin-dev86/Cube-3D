/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_calloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:54:39 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/25 19:55:11 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	*p_calloc(size_t count, size_t size)
{
	void *ptr;

	ptr = calloc(count, size);
	if (!ptr)
	{
		printf("Error: Memory allocation failed.\n");
		exit(1);
	}
	return (ptr);
}