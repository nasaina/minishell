/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:17:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/06 16:15:00 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_var_name(char *str, int i)
{
	int		j;
	int		len;
	char	*name;

	len = 0;
	if (str[i] == '$')
		i++;
	j = i;
	while (str[i] != 32 && str[i] != 34 && str[i] != 39 && str[i])
	{
		i++;
		len++;
	}
	name = malloc(len + 1);
	i = 0;
	while (i < len)
		name[i++] = str[j++];
	name[i] = 0;
	return (name);
}

int	no_quote(char *str, int i)
{
	int		count;

	count = 0;
	while (str[i] != 34 && str[i] != 39 && str[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	quote_simple(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i] && str[i] != '\'')
	{
		i++;
		count++;
	}
	return (count);
}

int	quote_double(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i] && str[i] != '"')
	{
		i++;
		count++;
	}
	return (count);
}

char	*str_insert(char *str, int count, int *i)
{
	char	*new;
	int		j;

	j = 0;
	new = malloc(count + 1);
	while (j < count)
	{
		new[j] = str[*i];
		j++;
		*i += 1;
	}
	new[j] = 0;
	return (new);
}

char	*join_char(char *str, char c)
{
	char	*result;
	char	*value;
	int		len;

	if (!str)
		result = ft_strdup(&c);
	else
	{
		len = ft_strlen(str);
		result = malloc(len + 2);
		ft_strlcpy(result, str, len + 1);
		result[len] = c;
		result[len + 1] = 0;
	}
	value = ft_strdup(result);
	free(result);
	return (value);
}

char	*expander(char *str, t_export *export)
{
	int			i;
	char		*result;
	char		*value;
	char		*name;
	size_t		j;
	static int	status;

	i = 0;
	result = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"')
			status = 1;
		if (str[i] == '\'' && status == 0)
		{
			result = join_char(result, str[i]);
			i++;
			while (str[i] != '\'' && str[i])
			{
				result = join_char(result, str[i]);
				i++;
			}
		}
		if (str[i] == '$' && str[i + 1] != '"' && str[i + 1])
		{
			name = get_var_name(str, i);
			i++;
			if (isdigit(name[0]))
			{
				i++;
				continue ;
			}
			value = ms_getenv(name, export);
			if (value)
			{
				result = ft_strjoin(result, value);
				free(value);
			}
			j = 0;
			while (j < ft_strlen(name))
			{
				j++;
				i++;
			}
			free (name);
		}
		result = join_char(result, str[i]);
		i++;
	}
	return (result);
}

t_chunk	*expanded(char *str, t_type type)
{
	int			i;
	int			count;
	char		*tmp;
	char		*result;
	char		**split;
	static int	is_quote;
	t_chunk		*chunks;

	i = 0;
	chunks = NULL;
	split = NULL;
	result = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			is_quote = 1;
			count = quote_double(str, i);
			tmp = str_insert(str, count, &i);
			if (str[i] == '"')
				i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			is_quote = 1;
			count = quote_simple(str, i);
			tmp = str_insert(str, count, &i);
			if (str[i] == '\'')
				i++;
		}
		else
		{
			is_quote = 0;
			count = no_quote(str, i);
			tmp = str_insert(str, count, &i);
		}
		result = ft_strjoin(result, tmp);
		free(tmp);
	}
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

t_expander	*expand_str(t_chunk *chunks, t_export *export)
{
	t_expander	*expanders;
	t_chunk		*tmp;
	t_chunk		*exp;
	t_chunk		*temp;
	char		*result;

	tmp = chunks;
	expanders = NULL;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		exp = NULL;
		result = expander(tmp->str, export);
		exp = expanded(result, tmp->type);
		temp = exp;
		while (temp)
		{
			add_expanders_back(&expanders, temp->str, temp->type);
			temp = temp->next;
		}
		tmp = tmp->next;
	}
	free_chunks(chunks);
	return (expanders);
}
