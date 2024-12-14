/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:38:22 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/14 13:59:30 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	unclosed_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i])
				i++;
			if (!str[i])
				return (1);
			else if (str[i] == '"' && str[i + 1])
				continue ;
			else if (str[i] == '"' && !str[i + 1])
				return (0);
		}
		else if (str[i] == '\'')
		{
						i++;
			while (str[i] != '\'' && str[i])
				i++;
			if (!str[i])
				return (1);
			else if (str[i] == '\'' && str[i + 1])
				continue ;
			else if (str[i] == '\'' && !str[i + 1])
				return (0);
		}
		if (i < (int)ft_strlen(str))
			i++;
	}
	return (0);
}
