/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:34:29 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/13 09:45:13 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lexer *get_args(t_lexer*args, char *str)
{
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		add_back(&args, str[i]);
		i++;
	}
	return (args);
}