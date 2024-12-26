/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:08:53 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 07:38:43 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_nword(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '$' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	check_split(char **str)
{
	if (!str[1])
		return (1);
	return (0);
}

int	token_nword(char *str, t_chunk **token, t_type type)
{
	if (!is_nword(str))
	{
		add_chunks_back(token, str, type);
		return (1);
	}
	return (0);
}

void	assemble_token(char *str, char *result, t_chunk **token, int i)
{
	if (!str[i])
	{
		add_chunks_back(token, result, WORD);
		if (result)
			free(result);
		result = NULL;
	}
}
