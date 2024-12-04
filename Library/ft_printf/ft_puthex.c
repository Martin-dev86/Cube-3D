/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:02:40 by cagarci2          #+#    #+#             */
/*   Updated: 2024/02/26 11:30:07 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned long long num, char c)
{
	int		count;
	char	*str;
	char	hexa[16];
	int		i;

	i = 0;
	count = 0;
	if (c == 'x')
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	if (num == 0)
		return (count += write(1, "0", 1));
	while (num != 0)
	{
		hexa[i++] = str[num % 16];
		num = num / 16;
	}
	while (i-- > 0)
	{
		count += ft_putchar(hexa[i]);
		if (count == -1)
			return (-1);
	}
	return (count);
}
