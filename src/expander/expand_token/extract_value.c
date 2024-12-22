/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:01:56 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/22 17:19:12 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	extract_status(char **result, int *i, char *str)
{
	if (str[*i] && str[*i] == '$' && str[*i + 1]
		&& str[*i + 1] == '?')
	{
		*i += 1;
		ms_exitstatus(result, i);
		return (1);
	}
	return (0);
}

void	extract_qvalue(char *str, char **result, int *i, t_env *env)
{
	char	*name;

	name = NULL;
	if (str[*i] && str[*i] == '$' && str[*i + 1] != '?' && str[*i + 1] != '$')
	{
		name_token(str, i, &name);
		env_value(result, i, env, name);
		free(name);
	}
	else if (str[*i] && str[*i] != '"' && str[*i] != '$')
	{
		*result = join_char(*result, str[*i]);
		*i += 1;
	}
}

int	extract_value(char *str, int *i, char **result, int status)
{
	if (str[*i] && extract_word(str, result, i, status))
		return (1);
	if (str[*i] && str[*i] == '"' && status != 1)
	{
		if (str[*i] && extract_double(str, result, i) == 1)
			return (1);
		else if (str[*i] && extract_double(str, result, i) == -1)
			return (-1);
	}
	else if (str[*i] && str[*i] == '\'' && status != 1)
		extract_single(str, result, i);
	return (0);
}
