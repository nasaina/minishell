/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:55:26 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 07:48:53 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**add_split(char *str, int	*status, int *i, t_chunk **token)
{
	char	**split;

	split = NULL;
	if (str[*i] && str[*i] == '$' && str[*i + 1]
		&& str[*i + 1] != '?' && *status != 1)
	{
		split = ignore_split(str, i, status, token);
		if (!split)
			return (NULL);
	}
	return (split);
}

int	split_all(t_chunk **token, char **result, int *status, char **split)
{
	if (*status == 1)
	{
		if (split_token(result, token, status, split))
			return (1);
	}
	else
		free_tab(split);
	return (0);
}

void	init_token(t_chunk **token, t_env *env, int *i, char **result)
{
	get_t_env(env);
	*token = NULL;
	*i = 0;
	*result = NULL;
}
