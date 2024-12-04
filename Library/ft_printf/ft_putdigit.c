/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:20:59 by cagarci2          #+#    #+#             */
/*   Updated: 2024/07/20 16:23:13 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_minnum(void)
{
	if (write(1, "-2147483648", 11) != 11)
		return (-1);
	return (11);
}

int	ft_putdigit(int num)
{
	int	count;

	count = 0;
	if (num == -2147483648)
		return (ft_minnum());
	if (num < 0)
	{
		count += ft_putchar('-');
		if (count == -1)
			return (-1);
		num *= -1;
	}
	if (num >= 10)
	{
		count += ft_putdigit(num / 10);
		if (count == -1)
			return (-1);
		count += ft_putdigit(num % 10);
		if (count == -1)
			return (-1);
	}
	else
		count += ft_putchar(num + '0');
	return (count);
}
