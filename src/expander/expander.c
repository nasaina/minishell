/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:17:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 13:56:19 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	env_value(char **result, int *i, t_env *env, char *name)
{
	char	*value;
	int		j;

	value = ms_getenv(name, env);
	if (!value)
	{
		*i += (int)ft_strlen(name);
		free(name);
		return ;
	}
	*result = join_free(*result, value, 0);
	free(value);
	j = 0;
	while (j < (int)ft_strlen(name))
	{
		j++;
		*i += 1;
	}
	free(name);
}

int	is_status(char *str, int i)
{
	if (!str)
		return (0);
	if (str[i] == '$' && str[i + 1] == '?')
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
	char	*name;
	t_env	*env;

	name = NULL;
	env = get_t_env(NULL);
	if (str[*i] && ignore_value(str, result, i, status))
		return (1);
	if (str[*i] && str[*i] == '$' && !is_status(str, *i)
		&& str[*i + 1] && !char_isquote(str[*i + 1]) && str[*i + 2])
	{
		if (name_token(str, i, &name))
			return (1);
		env_value(result, i, env, name);
	}
	if (str[*i] && is_status(str, *i))
		ms_exitstatus(result, i);
	if (*i >= (int)ft_strlen(str))
		return (0);
	*result = join_char(*result, str[*i]);
	*i += 1;
	return (0);
}
