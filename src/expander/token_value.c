/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:10:25 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 14:19:07 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expander(char *str, t_env *env)
{
	int		i;
	char	*result;
	int		status;

	result = NULL;
	status = 0;
	if (!str)
		return (NULL);
	i = 0;
	get_t_env(env);
	while (str[i])
	{
		if (i >= (int)ft_strlen(str))
			break ;
		if (insert_char(&result, str, &status, &i) == 1)
			continue ;
		if (i >= (int)ft_strlen(str))
			break ;
	}
	return (result);
}

t_chunk	*expand_token(char *result, int is_quote, t_type type)
{
	int		i;
	char	**split;
	t_chunk	*chunks;

	chunks = NULL;
	if (is_quote == 0)
	{
		i = 0;
		split = ft_split(result, 32);
		if (!split)
			return (NULL);
		while (split[i])
		{
			add_chunks_back(&chunks, split[i], type);
			free(split[i]);
			i++;
		}
		free(split);
	}
	else
		add_chunks_back(&chunks, result, WORD);
	free(result);
	return (chunks);
}

t_chunk	*expanded(char *str, t_type type, t_env *env)
{
	int			is_quote;
	char		*result;
	char		*str_expanded;
	t_chunk		*chunks;

	if (!str)
		return (NULL);
	str_expanded = expander(str, env);
	if (!str_expanded)
		return (NULL);
	is_quote = dquote_status(str_expanded);
	result = get_command(str_expanded);
	if (!result)
		return (NULL);
	free(str_expanded);
	chunks = expand_token(result, is_quote, type);
	return (chunks);
}

t_expander	*expand_str(t_chunk *chunks, t_env *env)
{
	t_expander	*expander;
	t_chunk		*tmp;
	t_chunk		*token;
	t_chunk		*temp;

	tmp = chunks;
	expander = NULL;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		token = NULL;
		token = expanded(tmp->str, tmp->type, env);
		temp = token;
		while (temp)
		{
			add_expanders_back(&expander, temp->str, temp->type);
			temp = temp->next;
		}
		tmp = tmp->next;
		free_chunks(token);
	}
	return (expander);
}
