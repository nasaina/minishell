/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:08:57 by nandrian          #+#    #+#             */
/*   Updated: 2024/07/05 13:31:15 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putnbr_hex(unsigned int c, unsigned int base, int upcase, int *len)
{
	char	*str;

	if (upcase == 1)
		str = "0123456789ABCDEF";
	else
		str = "0123456789abcdef";
	if (c < base)
		ft_putchar_len(str[c], len);
	else
	{
		ft_putnbr_hex(c / base, base, upcase, len);
		ft_putnbr_hex(c % base, base, upcase, len);
	}
}
