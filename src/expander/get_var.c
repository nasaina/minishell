/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:50:56 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/11 16:10:23 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_name(char *str)
{
	int		i;
	int		j;
	int		count;
	char	*name;

	count = 1;
	while (str[count] && str[count] != 32)
		count++;
	name = malloc(count + 1);
	i = 1;
	j = 0;
	while (j < count)
	{
		name[j] = str[i];
		j++;
		i++;
	}
	name[j] = '\0';
	return (name);
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

	var_name = get_name(str);
	while (export)
	{
		env = var_remove(export->env);
		if (!ft_strcmp(var_name, env))
			return (get_value(export->env));
		export = export->next;
	}
	return (NULL);
}

char	*ms_get(char *str, t_export *export)
{
	if (is_variable(str))
		return(ms_getenv(str, export));
	return (str);
}

t_expander	*expand_str(t_chunk *chunks, t_export *export)
{
	int			i;
	t_expander	*expander;
	t_expander	*current;
	char		**str;

	current = NULL;
	expander = NULL;
	while (chunks)
	{
		if (is_variable(chunks->str))
		{
			str = ft_split(ms_get(chunks->str, export), ' ');
			if (!str)
				return (NULL);
			i = 0;
			while (str[i])
			{
				add_expanders_back(&expander, str[i], WORD);
				i++;
			}
		}
		else
			add_expanders_back(&expander, chunks->str, chunks->type);
		chunks = chunks->next;
	}
	return (expander);
}
