/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:55:55 by nandrian          #+#    #+#             */
/*   Updated: 2024/03/24 14:55:39 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	len;
	char	in;

	len = ft_strlen(s);
	in = (char)c;
	while (len > 0 && *s != in)
	{
		s++;
		len--;
	}
	if (*s == in)
		return ((char *)s);
	return (NULL);
}
