/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:02:11 by nandrian          #+#    #+#             */
/*   Updated: 2024/03/23 09:26:26 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_digit(int len)
{
	char	*str;

	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 48;
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nb;
	int		len;

	nb = n;
	len = ft_intlen(n);
	str = ft_digit(len);
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = 45;
		nb = -nb;
	}
	i = len - 1;
	while (nb > 0)
	{
		str[i] = (nb % 10) + 48;
		nb /= 10;
		i--;
	}
	str[len] = '\0';
	return (str);
}
