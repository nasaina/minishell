/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:04:24 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 08:19:15 by nandrian         ###   ########.fr       */
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

char	*var_remove(char *str)
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

void	remove_env(t_env **env, char *str)
{
	t_env	*tmp;
	char	*to_remove;

	tmp = *env;
	if (tmp == NULL)
		return ;
	to_remove = var_remove(tmp->env);
	if (!ft_strcmp(to_remove, str))
	{
		*env = tmp->next;
		free(tmp->env);
		free(tmp);
		free(to_remove);
	}
	else
	{
		free(to_remove);
		remove_env(&(*env)->next, str);
	}
}

int	ms_unset(t_env **env, char **str)
{
	int	i;

	i = 0;
	if (!ft_strcmp(str[0], "unset"))
	{
		i++;
		if (str[i])
		{
			while (str[i])
			{
				remove_env(env, str[i]);
				i++;
			}
		}
	}
	return (0);
}
