/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:13:42 by maandria          #+#    #+#             */
/*   Updated: 2024/12/25 13:44:05 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*takepath_and_free(char *command, char **pathlist)
{
	char	*path_tmp;
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (pathlist[i])
	{
		path_tmp = ft_strjoin(pathlist[i], command);
		if (access(path_tmp, F_OK) == 0)
		{
			path = ft_strdup(path_tmp);
			free(path_tmp);
			free(command);
			free_tab(pathlist);
			return (path);
		}
		free(path_tmp);
		i++;
	}
	return (path);
}
