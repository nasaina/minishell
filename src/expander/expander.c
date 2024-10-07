/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:17:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/07 11:38:59 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_variable(char *str)
{
	int	i;

	i = 0;
	if (str[i] == 39)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	is_one_word(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != 32)
		i++;
	return (i);
}

char	*get_variable(char *str)
{
	char	*name;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '$' && !str[i])
		i++;
	i++;
	name = malloc((ft_strlen(str) - i) + 1);
	j = 0;
	while (str[i] && str[i] != 32)
	{
		name[j] = str[i];
		i++;
		j++;
	}
	name[j] = '\0';
	return (name);
}

char	*expander(char *str, char **envp)
{
	(void)envp;
	if (is_variable(str))
		return (getenv(get_variable(str)));
	else
		return (str);
	return (NULL);
}
