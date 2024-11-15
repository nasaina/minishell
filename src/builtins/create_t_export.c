/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_t_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:37:04 by nandrian          #+#    #+#             */
/*   Updated: 2024/11/12 09:05:56 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_export	*get_export(char *str)
{
	t_export	*export;

	export = malloc(sizeof(t_export));
	if (!export)
		return (NULL);
	export->env = str;
	export->next = NULL;
	return (export);
}

t_export	*export_last(t_export *export)
{
	while (export->next)
		export = export->next;
	return (export);
}

void	export_back(t_export **export, char *str)
{
	t_export	*element;
	t_export	*tmp;

	element = get_export(str);
	if (*export)
	{
		tmp = export_last(*export);
		tmp->next = element;
	}
	else
		*export = element;
}
