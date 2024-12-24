/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:10:25 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 09:34:59 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_chunk	*expander(char *str, t_env *env, t_type type)
{
	int		i;
	int		status;
	char	*result;
	t_chunk	*token;
	char	**split;

	init_token(&token, env, &i, &result);
	status = 0;
	if (token_nword(str, &token, type))
		return (token);
	while (str[i])
	{
		if (extract_value(str, &i, &result, status) == 1)
			continue ;
		else if (extract_value(str, &i, &result, status) == -1)
			break ;
		split = add_split(str, &status, &i, &token);
		if (!split)
			continue ;
		if (split_all(&token, &result, &status, split))
			continue ;
	}
	if (result == NULL)
		result = ft_strdup("");
	assemble_token(str, result, &token, i);
	return (token);
}

t_expander	*expand_str(t_chunk *chunks, t_env *env)
{
	t_expander	*expand_token;
	t_chunk		*tmp;
	t_chunk		*token;
	t_chunk		*temp;

	tmp = chunks;
	if (!tmp)
		return (NULL);
	expand_token = NULL;
	while (tmp)
	{
		token = NULL;
		token = expander(tmp->str, env, tmp->type);
		temp = token;
		while (temp)
		{
			add_expanders_back(&expand_token, temp->str, temp->type);
			temp = temp->next;
		}
		tmp = tmp->next;
		free_chunks(token);
	}
	free_chunks(chunks);
	return (expand_token);
}
