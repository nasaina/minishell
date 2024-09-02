/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:05:39 by nandrian          #+#    #+#             */
/*   Updated: 2024/07/05 13:31:18 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putnbr_len(int c, int *len)
{
	char	*str;

	str = "0123456789";
	if (c == -2147483648)
	{
		write (1, "-2147483648", 11);
		*len += 11;
	}
	else if (c < 0)
	{
		ft_putchar_len('-', len);
		c *= -1;
		ft_putnbr_len(c, len);
	}
	else if (c > 9)
	{
		ft_putnbr_len(c / 10, len);
		ft_putnbr_len(c % 10, len);
	}
	else
		ft_putchar_len(str[c], len);
}
