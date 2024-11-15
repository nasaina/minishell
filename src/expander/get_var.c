/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:50:56 by nandrian          #+#    #+#             */
/*   Updated: 2024/11/15 06:29:49 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_name(char *str)
{
	int		i;
	int		j;
	int		count;
	char	*name;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != 36 && str[i])
		i++;
	if (str[i] == 36)
		i++;
	count = 0;
	while (str[i] && str[i] != 32)
	{
		i++;
		count++;
	}
	name = malloc(count + 1);
	j = 0;
	i -= count;
	while (j < count)
		name[j++] = str[i++];
	name[j] = '\0';
	return (name);
}

char	*get_before(char *str)
{
	int		i;
	int		j;
	char	*before;

	i = 0;
	while (str[i] && str[i] != 36)
		i++;
	if (i != 0 && str[i])
	{
		before = malloc(i + 1);
		j = 0;
		while (j < i)
		{
			before[j] = str[j];
			j++;
		}
		before[j] = '\0';
		return (before);
	}
	return (NULL);
}

char	*get_value(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*value;

	i = 0;
	while (str[i] != 61 && str[i])
		i++;
	if (str[i] == 61)
		i++;
	else
		return (NULL);
	len = ft_strlen(str) - i;
	value = malloc(len + 1);
	j = 0;
	while (str[i])
		value[j++] = str[i++];
	value[j] = '\0';
	return (value);
}

char	*ms_getenv(char *str, t_export *export)
{
	char	*env;
	char	*var_name;
	char	*value;

	var_name = get_name(str);
	while (export)
	{
		env = var_remove(export->env);
		if (!ft_strcmp(var_name, env))
		{
			free(var_name);
			free(env);
			value = get_value(export->env);
			return (value);
		}
		free(env);
		export = export->next;
	}
	free(var_name);
	value = ft_strdup("(null)");
	return (value);
}

char	*ms_get(char *str, t_export *export)
{
	char	*before;
	char	*value;

	if (is_variable(str))
	{
		before = get_before(str);
		value = ms_getenv(str, export);
		if (before && value)
			value = ft_strjoin(before, value);
		free(before);
		return (value);
	}
	return (str);
}

void	add_variable(t_expander **expander, char *str, t_export *export)
{
	int		i;
	char	*env;
	char	**split;

	env = ms_get(str, export);
	if (env)
	{
		split = ft_split(env, ' ');
		free(env);
		i = 0;
		while (split[i])
		{
			add_expanders_back(expander, split[i], WORD);
			i++;
		}
		free(split);
	}
	else
		add_expanders_back(expander, NULL, WORD);
}

t_expander	*expand_str(t_chunk *chunks, t_export *export)
{
	t_expander	*expander;
	t_chunk		*tmp;

	expander = NULL;
	tmp = chunks;
	while (tmp)
	{
		if (is_variable(tmp->str))
			add_variable(&expander, tmp->str, export);
		else
			add_expanders_back(&expander, tmp->str, tmp->type);
		tmp = tmp->next;
	}
	return (expander);
}
