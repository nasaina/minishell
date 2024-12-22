/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_t_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:37:04 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/06 09:50:46 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*get_env(char *str)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->env = ft_strdup(str);
	env->next = NULL;
	return (env);
}

t_env	*env_last(t_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

void	env_back(t_env **env, char *str)
{
	t_env	*element;
	t_env	*tmp;

	element = get_env(str);
	if (*env)
	{
		tmp = env_last(*env);
		tmp->next = element;
	}
	else
		*env = element;
}

t_env	*get_t_env(t_env *env)
{
	static t_env	*data = NULL;

	if (env == NULL)
		return (data);
	data = env;
	return (data);
}
