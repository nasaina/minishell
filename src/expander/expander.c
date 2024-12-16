/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:17:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/15 17:02:39 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	export_value(char **result, int *i, t_export *export, char *name)
{
	char	*value;
	int		j;

	value = ms_getenv(name, export);
	if (value)
	{
		*result = ft_strjoin(*result, value);
		free(value);
	}
	j = 0;
	while (j < (int)ft_strlen(name))
	{
		j++;
		*i += 1;
	}
	free (name);
}

char	*expander(char *str, t_export *export)
{
	int			i;
	char		*result;
	char		*name;
	int			status;

	result = NULL;
	status = 0;
	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (ignore_value(str, &result, &i, &status))
			continue ;
		if (str[i] == '$' && !char_isquote(str[i + 1]) && str[i + 1])
		{
			if (name_token(str, &i, &name))
				continue ;
			export_value(&result, &i, export, name);
		}
		result = join_char(result, str[i]);
		if (i >= (int)ft_strlen(str))
			break ;
		i++;
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

t_chunk	*expanded(char *str, t_type type, t_export *export)
{
	char		*result;
	int			is_quote;
	t_chunk		*chunks;
	char		*str_expanded;

	if (!str)
		return (NULL);
	str_expanded = expander(str, export);
	is_quote = dquote_status(str_expanded);
	result = get_command(str_expanded);
	free(str_expanded);
	chunks = expand_token(result, is_quote, type);
	return (chunks);
}

t_expander	*expand_str(t_chunk *chunks, t_export *export)
{
	t_expander	*expanders;
	t_chunk		*tmp;
	t_chunk		*exp;
	t_chunk		*temp;

	tmp = chunks;
	expanders = NULL;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		exp = NULL;
		exp = expanded(tmp->str, tmp->type, export);
		temp = exp;
		while (temp)
		{
			add_expanders_back(&expanders, temp->str, temp->type);
			temp = temp->next;
		}
		tmp = tmp->next;
		free_chunks(exp);
	}
	return (expanders);
}
