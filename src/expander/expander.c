/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:17:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/19 17:37:19 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_exitstatus(char **result, int *i)
{
	int		fd;
	char	*str;
	int		len;

	fd = open(".ms_status", O_RDONLY);
	if (fd == -1)
	{
		join_free(*result, "0", 0);
		add_quote(result);
		*i += 2;
		return ;
	}
	str = get_next_line(fd);
	if (!str)
	{
		*i += 2;
		return ;
	}
	len = ft_strlen(str);
	str[len] = 0;
	add_quote(&str);
	*result = join_free(*result, str, 0);
	free(str);
	*i += len + 1;
	close(fd);
}

void	export_value(char **result, int *i, t_export *export, char *name)
{
	char	*value;
	int		j;

	value = ms_getenv(name, export);
	if (!value)
	{
		*i += (int)ft_strlen(name);
		return ;
	}
	add_quote(&value);
	*result = join_free(*result, value, 0);
	free(value);
	j = 0;
	while (j < (int)ft_strlen(name))
	{
		j++;
		*i += 1;
	}
	free (name);
}

int	is_status(char *str, int i)
{
	if (!str)
		return (0);
	if (str[i] == '$' && str[i + 1] == '?'
		&& (!str[i + 2] || str[i + 2] == '"' || str[i + 2] == '\''))
		return (1);
	return (0);
}

void	add_quote(char **result)
{
	char	*str;
	char	*name;
	int		len;
	int		i;
	int		j;

	name = *result;
	if (!name)
		return ;
	len = (int)ft_strlen(*result);
	str = malloc(len + 3);
	if (!str)
		return ;
	str[0] = '"';
	i = 0;
	j = 1;
	while (name[i])
		str[j++] = name[i++];
	str[j] = '"';
	str[j + 1] = 0;
	free(*result);
	*result = ft_strdup(str);
	free(str);
}

int	insert_char(char **result, char *str, int *status, int *i)
{
	char		*name;
	t_export	*export;

	name = NULL;
	export = get_t_env(NULL);
	if (ignore_value(str, result, i, status))
		return (1);
	if (str[*i] == '$' && !is_status(str, *i)
		&& !char_isquote(str[*i + 1]) && str[*i + 2])
	{
		if (name_token(str, i, &name))
			return (1);
		export_value(result, i, export, name);
	}
	if (is_status(str, *i))
		ms_exitstatus(result, i);
	*result = join_char(*result, str[*i]);
	*i += 1;
	return (0);
}

char	*expander(char *str, t_export *export)
{
	int		i;
	char	*result;
	int		status;

	result = NULL;
	status = 0;
	if (!str)
		return (NULL);
	i = 0;
	get_t_env(export);
	while (str[i])
	{
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

t_chunk	*expanded(char *str, t_type type, t_export *export)
{
	int			is_quote;
	char		*result;
	char		*str_expanded;
	t_chunk		*chunks;

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
