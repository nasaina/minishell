/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:32:25 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/08 15:13:52 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_expander	*create_expander(char *str, t_type type)
{
	t_expander	*expander;

	expander = (t_expander *)malloc(sizeof(t_expander));
	if (!expander)
		return (NULL);
	expander->type = type;
	expander->cmd = ft_strdup(str);
	expander->next = NULL;
	return (expander);
}

t_expander	*expander_last(t_expander *args)
{
	while (args->next)
		args = args->next;
	return (args);
}

void	add_expanders_back(t_expander **expander, char *str, t_type type)
{
	t_expander	*element;
	t_expander	*tmp;

	if (!str)
		return ;
	element = create_expander(str, type);
	if (*expander)
	{
		tmp = expander_last(*expander);
		tmp->next = element;
	}
	else
		*expander = element;
}
