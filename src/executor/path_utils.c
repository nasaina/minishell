/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:13:42 by maandria          #+#    #+#             */
/*   Updated: 2024/12/25 13:55:33 by maandria         ###   ########.fr       */
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

char	**create_dir(void)
{
	char	*list;
	char	**pl;

	list = ft_strdup("./");
	pl = malloc(2 * sizeof(char *));
	pl[0] = list;
	pl[1] = NULL;
	return (pl);
}
