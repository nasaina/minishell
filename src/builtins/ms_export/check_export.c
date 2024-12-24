/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:18:54 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 16:46:03 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*env_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(i + 1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = 0;
	return (name);
}

int	double_input(char **str, int i, char *args)
{
	char	*name;

	i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		name = env_name(str[i]);
		if (!ft_strcmp(args, name))
		{
			free(name);
			return (1);
		}
		i++;
	}
	free(name);
	return (0);
}

int	is_invalidname(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	while (str[i])
	{
		if (str[i] && !ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	check_status(char **args)
{
	int		i;
	char	*name;

	i = 0;
	while (args[i])
	{
		name = NULL;
		name = env_name(args[i]);
		if (is_invalidname(name))
		{
			free(name);
			return (1);
		}
		free(name);
		i++;
	}
	return (0);
}
