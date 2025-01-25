/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:17:23 by cagarci2          #+#    #+#             */
/*   Updated: 2025/01/25 16:06:37 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;

	if ((unsigned char *)dst == 0 || (unsigned char *)src == 0)
		return (0);
	p_src = (unsigned char *)src;
	p_dst = (unsigned char *)dst;
	while (n > 0)
	{
		*p_dst = *p_src;
		p_dst++;
		p_src++;
		n--;
	}
	return (dst);
}
