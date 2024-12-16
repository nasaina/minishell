/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:23:53 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/16 14:49:45 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_last(char *str)
{
	char	*last;
	int		i;
	int		j;
	int		len;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	len = ft_strlen_gnl(str);
	last = malloc(len - i + 1);
	if (!last)
		return (NULL);
	j = 0;
	while (str[i])
	{
		last[j] = str[i + 1];
		i++;
		j++;
	}
	last[j] = '\0';
	free (str);
	return (last);
}

char	*get_first(char *str)
{
	char	*first;
	int		i;
	int		j;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	first = malloc(i + 2);
	j = 0;
	while (j < i + 1)
	{
		first[j] = str[j];
		j++;
	}
	first[j] = '\0';
	return (first);
}

char	*ft_read(int fd, char *stash)
{
	int		nread;
	char	*buffer;

	nread = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	while (nread > 0 && !is_newline(stash))
	{
		nread = read(fd, buffer, BUFFER_SIZE);
		if (nread > 0)
		{
			buffer[nread] = '\0';
			stash = ft_strjoin_gnl(stash, buffer);
		}
	}
	if (nread == -1)
		return (free(buffer), NULL);
	free (buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*last;
	char		*first;

	if (!is_newline(last))
		last = ft_read(fd, last);
	first = get_first(last);
	if (first == NULL)
		return (NULL);
	last = get_last(last);
	if (last[0] == '\0' )
	{
		free (last);
		last = NULL;
	}
	return (first);
}
