/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:04:24 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/09 11:23:31 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_unset(t_export **export, t_chunk *chunks)
{
	int			i;
	t_export	*tmp;
	t_export	*del;

	if (!ft_strcmp(chunks->str, "unset"))
	{
		chunks = chunks->next;
		if (chunks)
		{
			while (chunks)
			{
				tmp = *export;
				while (tmp)
				{
					i = 0;
					while (tmp->env[i] != 61 && tmp->env[i])
						i++;
					if (!ft_strncmp(chunks->str, tmp->env, i))
					{
						del = tmp;
						tmp = tmp->next;
						free(del);
					}
					if (tmp->next)
						tmp = tmp->next;
					else
						tmp = NULL;
				}
				chunks = chunks->next;
			}
		}
	}
}
