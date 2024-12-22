/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 08:20:55 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/22 08:49:14 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	split_token(char **result, t_chunk *token, int *status, char **split)
{
	*result = join_free(*result, split[0], 0);
	add_chunks_back(&token, *result, WORD);
	int	j = 1;
	if (!split[j])
		return (1);
	while (split[j + 1])
	{
		add_chunks_back(&token, split[j], WORD);
		free(split[j]);
		j++;
	}
	*result = join_free(NULL, split[j], 1);
	free(split[j]);
	free(split);
	*status = 0;
	return (0);
}
