/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:04:29 by nandrian          #+#    #+#             */
/*   Updated: 2024/03/24 15:40:35 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	char	*in;

	i = ft_strlen(str) + 1;
	in = NULL;
	while (i > 0)
	{
		if (*str == (char)c)
			in = (char *)str;
		i--;
		str++;
	}
	return (in);
}
