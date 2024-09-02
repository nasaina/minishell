/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 06:46:15 by nandrian          #+#    #+#             */
/*   Updated: 2024/03/23 09:25:04 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *src, int c, size_t n)
{
	size_t	i;
	char	*out;

	i = 0;
	out = src;
	while (i < n)
	{
		out[i] = c;
		i++;
	}
	return (src);
}
