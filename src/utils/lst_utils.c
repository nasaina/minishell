/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:50:44 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/13 09:45:55 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lexer	*create(char c)
{
	t_lexer	*args;
	
	args = malloc(sizeof(t_lexer));
	args->c = c;
	args->next = NULL;
	return (args);
}

t_lexer	*lst_last(t_lexer *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back(t_lexer **args, char c)
{
	t_lexer	*element;
	t_lexer	*tmp;

	element = create(c);
	if (*args)
	{
		tmp = lst_last(*args);
		tmp->next = element;
	}
	else
		*args = element;	
}

void	add_front(t_lexer **args, char c)
{
	t_lexer	*tmp;

	tmp = create(c);
	tmp->next = *args;
	*args = tmp;
}
