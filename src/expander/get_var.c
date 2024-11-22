/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:50:56 by nandrian          #+#    #+#             */
/*   Updated: 2024/11/22 15:15:12 by nandrian         ###   ########.fr       */
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

char	*ms_getenv(char *name, t_export *export)
{
	char	*env;
	char	*value;

	value = NULL;
	while (export)
	{
		env = var_remove(export->env);
		if (!ft_strcmp(name, env))
		{
			free(env);
			value = get_value(export->env);
			return (value);
		}
		free(env);
		export = export->next;
	}
	return (value);
}
