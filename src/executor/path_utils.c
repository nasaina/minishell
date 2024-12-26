/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:13:42 by maandria          #+#    #+#             */
/*   Updated: 2024/12/26 09:13:58 by nandrian         ###   ########.fr       */
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

void	stat_isdir(t_ast *ast, int *status)
{
	struct stat	*st;

	st = ft_calloc(sizeof(struct stat), 1);
	stat(ast->cmd->args[0], st);
	if (S_ISDIR(st->st_mode))
	{
		path_error(ast, ": Is a directory\n");
		*status = 126;
	}
	else
		path_error(ast, ": command not found\n");
	free(st);
}
