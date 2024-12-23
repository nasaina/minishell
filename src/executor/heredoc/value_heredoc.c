/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:24:57 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/22 18:22:06 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*expand_heredoc(char *file, char *str, t_env *env)
{
	char	*result;

	if (!str)
		return (NULL);
	result = NULL;
	if (!is_expandable(file) && is_variable(str))
		result = hdoc_expander(str, env);
	else
		result = ft_strdup(str);
	return (result);
}

int	heredoc_input(char *str, int *i, t_env *env, char **result)
{
	char	*name;

	name = NULL;
	if (str[*i] == '$' && !char_isquote(str[*i + 1]) && str[*i + 1])
	{
		if (name_token(str, i, &name))
		{
			free(name);
			return (1);
		}
		env_value(result, i, env, name);
	}
	free(name);
	if (str[*i])
	{
		*result = join_char(*result, str[*i]);
		*i += 1;
	}
	return (0);
}

int	quote_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (char_isquote(str[i]))
			count++;
		i++;
	}
	return (count);
}

char	*ignore_quote(char	*str)
{
	char	*result;
	int		count;
	int		i;

	count = quote_count(str);
	result = malloc(ft_strlen(str) - count + 1);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (char_isquote(str[i]) && str[i])
			i++;
		if (str[i])
		{
			result[count] = str[i];
			count++;
			i++;
		}
	}
	result[count] = 0;
	return (result);
}
