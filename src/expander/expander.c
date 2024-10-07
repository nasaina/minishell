/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:17:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/07 17:12:44 by nandrian         ###   ########.fr       */
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

int	is_one_word(char *str, int i)
{
	if (!str[i])
		return (0);
	while (str[i] && str[i] != 32 && str[i] != 34)
		i++;
	return (i);
}

char	*get_variable(char *str)
{
	char	*name;
	int		i;
	int		j;
	int		count;

	i = 0;
	while (str[i] != '$')
		i++;
	if (str[i] == '$')
		i++;
	count = is_one_word(str, i);
	name = malloc((count - i) + 1);
	j = 0;
	while (j < count)
	{
		if (str[i] != 34)
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
