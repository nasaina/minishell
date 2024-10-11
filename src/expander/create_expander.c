/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:32:25 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/11 15:51:09 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_expander	*create_expanders(char *str, t_type type)
{
	t_expander	*expanders;

	expanders = (t_expander *)malloc(sizeof(t_expander));
	if (!expanders)
		return (NULL);
	expanders->type = type;
	expanders->cmd = str;
	expanders->next = NULL;
	return (expanders);
}

t_expander	*expander_last(t_expander *args)
{
	while (args->next)
		args = args->next;
	return (args);
}

void	add_expanders_back(t_expander **args, char *str, t_type type)
{
	t_expander	*element;
	t_expander	*tmp;

	element = create_expanders(str, type);
	if (*args)
	{
		tmp = expander_last(*args);
		tmp->next = element;
	}
	else
		*args = element;
}
