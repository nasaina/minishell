/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:23:34 by nandrian          #+#    #+#             */
/*   Updated: 2024/03/23 09:25:19 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*out;
	char	*in;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	out = (char *)dest;
	in = (char *)src;
	i = 0;
	if (out > in)
	{
		while (n-- > 0)
			out[n] = in[n];
	}
	else
	{
		while (i < n)
		{
			out[i] = in[i];
			i++;
		}
	}
	return (dest);
}
