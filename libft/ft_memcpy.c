/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:02:23 by nandrian          #+#    #+#             */
/*   Updated: 2024/03/24 14:25:01 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*out;
	unsigned char	*in;

	if (!dest && !src)
		return (dest);
	out = (unsigned char *)dest;
	in = (unsigned char *)src;
	while (n > 0)
	{
		*out++ = *in++;
		n--;
	}
	return (dest);
}
