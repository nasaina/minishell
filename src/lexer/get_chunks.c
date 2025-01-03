/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chunks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:35:17 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/21 14:21:28 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_chunk	*create_chunks(char *str, t_type type)
{
	t_chunk	*chunks;

	chunks = (t_chunk *)malloc(sizeof(t_chunk));
	if (!chunks)
		return (NULL);
	chunks->type = type;
	chunks->str = ft_strdup(str);
	chunks->next = NULL;
	return (chunks);
}

t_chunk	*chunk_last(t_chunk *args)
{
	while (args->next)
		args = args->next;
	return (args);
}

void	add_chunks_back(t_chunk **args, char *str, t_type type)
{
	t_chunk	*element;
	t_chunk	*tmp;

	if (!str)
		return ;
	element = create_chunks(str, type);
	if (*args)
	{
		tmp = chunk_last(*args);
		tmp->next = element;
	}
	else
		*args = element;
}

void	add_chunks_front(t_chunk **args, char *str, t_type type)
{
	t_chunk	*tmp;

	tmp = create_chunks(str, type);
	tmp->next = *args;
	*args = tmp;
}
