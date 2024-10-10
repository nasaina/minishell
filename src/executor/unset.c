/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:04:24 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/10 22:00:08 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	len_to_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 61)
			return (i);
		i++;
	}
	return (i);
}

char *var_remove(char *str)
{
	int		count;
	int		i;
	char	*to_remove;

	count = len_to_equal(str);
	to_remove = malloc((count + 1) * sizeof(char));
	i = 0;
	while (i < count)
	{
		to_remove[i] = str[i];
		i++;
	}
	to_remove[i] = '\0';
	return (to_remove);
}

void	remove_env(t_export **export, char *str)
{
	t_export	*tmp;
	char		*to_remove;

	tmp = *export;
	if (tmp == NULL)
		return ;
	to_remove = var_remove(tmp->env);
	if (!ft_strcmp(to_remove, str))
	{
		*export = tmp->next;
		free(tmp);
		free(to_remove);
	}
	else
	{		
		free(to_remove);
		remove_env(&(*export)->next, str);
	}
}

void	ms_unset(t_export **export, t_chunk *chunks)
{
	/*t_export	*tmp;*/
	t_chunk		*token;

	/*tmp = *export;*/
	token = chunks;
	if (!ft_strcmp(token->str, "unset"))
	{
		token = token->next;
		if (token)
		{
			while (token)
			{
				remove_env(export, token->str);
				token = token->next;
			}
		}
	}
}
