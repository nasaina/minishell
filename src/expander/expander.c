/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:17:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/12 16:07:47 by nandrian         ###   ########.fr       */
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

void	ignore_value(char	*str, char **result, int *i, int *status)
{
	if (str[*i] == '"')
		*status = 1;
	if (str[*i] == '\'' && *status == 0)
	{
		*result = join_char(*result, str[*i]);
		*i += 1;
		while (str[*i] != '\'' && str[*i])
		{
			*result = join_char(*result, str[*i]);
			*i += 1;
		}
	}
}

char	*export_value(char **result, int *i, t_export *export, char *name)
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
	return (value);
}

int	name_token(char *str, int *i, char **name)
{
	*name = get_var_name(str, *i);
	*i += 1;
	if (isdigit(*name[0]))
	{
		*i += 1;
		return (1);
	}
	return (0);
}

char	*expander(char *str, t_export *export)
{
	int			i;
	char		*result;
	char		*value;
	char		*name;
	int			status;

	result = NULL;
	status = 0;
	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ignore_value(str, &result, &i, &status);
		if (str[i] == '$' && str[i + 1] != '"' && str[i + 1] != '\'' && str[i + 1])
		{
			if (name_token(str, &i, &name))
				continue ;
			value = export_value(&result, &i, export, name);
		}
		result = join_char(result, str[i]);
		i++;
	}
	return (result);
}

char	*handle_dquote(char *str, int *i)
{
	int		count;
	char	*result;

	*i += 1;
	count = quote_double(str, *i);
	result = str_insert(str, count, i);
	if (str[*i] == '"')
		*i += 1;
	return (result);
}

char	*handle_squote(char *str, int *i)
{
	int		count;
	char	*result;

	*i += 1;
	count = quote_simple(str, *i);
	result = str_insert(str, count, i);
	if (str[*i] == '\'')
		*i += 1;
	return (result);
}

int	dquote_status(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

char	*get_command(char *str)
{
	int		i;
	int		count;
	char	*tmp;
	char	*result;

	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
			tmp = handle_squote(str, &i);
		else if (str[i] == '"')
			tmp = handle_dquote(str, &i);
		else
		{
			count = no_quote(str, i);
			tmp = str_insert(str, count, &i);
		}
		result = ft_strjoin(result, tmp);
		free(tmp);
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
	result = get_command(str_expanded);
	is_quote = dquote_status(str_expanded);
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
	}
	free_chunks(exp);
	free_chunks(chunks);
	return (expanders);
}
