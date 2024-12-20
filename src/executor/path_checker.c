/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:12:38 by maandria          #+#    #+#             */
/*   Updated: 2024/12/20 12:51:32 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**path_list(t_env *env)
{
	t_env	*tmp;
	char	*list; 
	char	**pl;

	list = NULL;
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->env, "PATH=", 5) == 0)
		{
			list = tmp->env;
			break ;
		}
		else
			tmp = tmp->next;
	}
	pl = ft_split(list + 5, ':');
	int	i = 0;
	while (pl[i])
		i++;
	return (pl);
}

char	**take_env(t_env *env)
{
	int		i;
	char	**envp;
	t_env	*tmp;

	tmp = env;
	i = 0;
	envp = ft_calloc(1024, sizeof(char *));
	if (!envp)
		return (NULL);
	while (tmp)
	{
		envp[i] = ft_strdup(tmp->env);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
