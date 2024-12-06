/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:47:47 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/06 14:59:54 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_next(char *str, int i)
{
	while (str[i] == 32 && str[i])
		i += 1;
	if (!str[i])
		return (0);
	return (1);
}

int	isredirection(char c)
{
	char	*str;

	str = "<>";
	if (ft_strchr(str, c))
		return (1);
	return (0);
}

int	is_redirok(char *str, int i)
{
	if (isredirection(str[i]) && !isredirection(str[i + 1]))
		return (1);
	if (isredirection(str[i]) && str[i + 1] == str[i]
		&& !isredirection(str[i + 2]))
		return (1);
	if (str[i] == '<' && str[i + 1] == '>'
		&& !isredirection(str[i + 2]))
		return (1);
	return (0);
}

int	check_redirection(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (isredirection(str[i]))
		{
			if ((!is_redirok(str, i)) || !check_next(str, i + 1))
			{
				printf("Syntax error\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}
