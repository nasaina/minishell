/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:50:56 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 07:59:31 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	*ms_getenv(char *name, t_env *env)
{
	char	*str;
	char	*value;

	value = NULL;
	while (env)
	{
		str = var_remove(env->env);
		if (!ft_strcmp(name, str))
		{
			free(str);
			value = get_value(env->env);
			return (value);
		}
		free(str);
		env = env->next;
	}
	return (value);
}
