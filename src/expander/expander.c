/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:17:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/11/22 16:00:34 by nandrian         ###   ########.fr       */
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
	while (str[i] != 32 && str[i] != 34 && str[i])
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
	while (str[i] && str[i] != '\"')
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
	int		len;

	if (!str)
	{
		result = malloc(2);
		result[0] = c;
		result[1] = 0;
	}
	else
	{
		len = ft_strlen(str);
		result = malloc(len + 2);
		ft_strlcpy(result, str, len + 1);
		result[len] = c;
		result[len + 1] = 0;
	}
	return (result);
}

char	*expander(char *str, t_export *export)
{
	int		i;
	char	*result;
	char	*value;
	char	*name;
	size_t	j;

	i = 0;
	result = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			result = join_char(result, str[i]);
			i++;
			while (str[i] != '\'' && str[i])
			{
				result = join_char(result, str[i]);
				i++;
			}
		}
		if (str[i] == '$')
		{
			name = get_var_name(str, i);
			i++;
			j = 0;
			value = ms_getenv(name, export);
			if (value)
			{
				result = ft_strjoin(result, value);
				free(value);
			}
			while (j < ft_strlen(name))
			{
				j++;
				i++;
			}
		}
		result = join_char(result, str[i]);
		i++;
	}
	return (result);
}

char	*expanded(char *token, t_export *export)
{
	int		i;
	int		count;
	char	*new;
	char	*out;
	char	*str;

	i = 0;
	(void)export;
	out = NULL;
	str = expander(token, export);
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			count = quote_simple(str, i);
			new = str_insert(str, count, &i);
			if (str[i] == '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			count = quote_double(str, i);
			new = str_insert(str, count, &i);
			if (str[i] == '\"')
				i++;
		}
		else
		{
			count = no_quote(str, i);
			new = str_insert(str, count, &i);
		}
		out = ft_strjoin(out, new);
		free(new);
	}
	return (out);
}

t_expander	*expand_str(t_chunk *chunks, t_export *export)
{
	t_expander	*expander = NULL;
	t_chunk		*tmp;
	char		*str;

	tmp = chunks;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		str = expanded(tmp->str, export);
		add_expanders_back(&expander, str, tmp->type);
		tmp = tmp->next;
	}
	return (expander);
}
