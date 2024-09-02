/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:34:53 by nandrian          #+#    #+#             */
/*   Updated: 2024/03/24 14:22:44 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	unsigned char	*out1;
	unsigned char	*out2;

	out1 = (unsigned char *)s1;
	out2 = (unsigned char *)s2;
	while (size > 0)
	{
		if (*out1 != *out2)
		{
			if (*out1 > *out2)
				return (1);
			if (*out1 < *out2)
				return (-1);
			else
				return (0);
		}
		out1++;
		out2++;
		size--;
	}
	return (0);
}
