/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:16:46 by maandria          #+#    #+#             */
/*   Updated: 2024/12/17 16:10:58 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	path_error(t_ast *ast)
{
	ft_putstr_fd(ast->cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}
char	*check_path(char **pathlist, t_ast *ast)
{
	int		i;
	char	*path;
	char	*command;
	char	*tmp;

	i = 0;
	command = ft_strjoin("/", ast->cmd->args[0]);
	while (pathlist[i])
	{
		if (access(ft_strjoin(pathlist[i], command), F_OK) == 0)
		{
			tmp = ft_strjoin(pathlist[i], "/");
			path  = ft_strjoin(tmp, ast->cmd->args[0]);
			free(tmp);
			return (path);
		}
		else
			i++;
	}
	if (ast->cmd->args[0] != NULL)
		path_error(ast);
	return (NULL);
}


char	*check_access(t_ast *ast)
{
	char	*path;
	char	*command;

	command = ast->cmd->args[0];
	path = NULL;
	if (access(command, F_OK) == 0)
	{
		path  = ast->cmd->args[0];
		return (path);
	}
	else
		perror(command);
	return (NULL);
}
