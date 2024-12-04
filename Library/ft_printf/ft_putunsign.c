/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:24:15 by cagarci2          #+#    #+#             */
/*   Updated: 2023/12/21 13:39:33 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsign(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_putunsign(n / 10);
		if (count == -1)
			return (-1);
		count += ft_putunsign(n % 10);
		if (count == -1)
			return (-1);
	}
	else
	{
		count += ft_putchar(n + '0');
		if (count == -1)
			return (-1);
	}
	return (count);
}
