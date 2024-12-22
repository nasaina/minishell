/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 08:20:55 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/22 14:10:11 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	extract_double(char *str, char **result, int *i)
{
	t_env	*env;

	env = get_t_env(NULL);
	*i += 1;
	while (str[*i] && str[*i] != '"')
	{
		ignore_special(str, result, i);
		extract_qvalue(str, result, i, env);
		if (*i > (int)ft_strlen(str))
			return (-1);
	}
	if (str[*i] && str[*i] == '"')
	{
		i++;
		return (1);
	}
	return (0);
}

int	extract_word(char *str, char **result, int *i, int status)
{
	if (status == 1)
		return (0);
	if (str[*i])
	{
		while (str[*i] && (str[*i] != '\'' && str[*i] != '"' && str[*i] != '$'))
		{
			*result = join_char(*result, str[*i]);
			*i += 1;
		}
	}
	ignore_special(str, result, i);
	return (0);
}

int	extract_single(char *str, char **result, int *i)
{
	*i += 1;
	while (str[*i] && str[*i] != '\'')
	{
		*result = join_char(*result, str[*i]);
		*i += 1;
	}
	if (str[*i] && str[*i] == '\'')
		*i += 1;
	return (0);
}

char	*extract_noquote(char *str, int *status, int *i)
{
	t_env	*env;
	char	*name;
	char	*tmp;

	env = get_t_env(NULL);
	*status = 1;
	tmp = NULL;
	name_token(str, i, &name);
	env_value(&tmp, i, env, name);
	if (tmp == NULL)
	{
		*status = 0;
		free(name);
		return (NULL);
	}
	free(name);
	return (tmp);
}

int	split_token(char **result, t_chunk **token, int *status, char **split)
{
	int	j;

	*result = join_free(*result, split[0], 0);
	add_chunks_back(token, *result, WORD);
	free(*result);
	j = 1;
	while (split[j + 1])
	{
		add_chunks_back(token, split[j], WORD);
		j++;
	}
	*result = ft_strjoin(NULL, split[j]);
	free_tab(split);
	*status = 0;
	return (0);
}
