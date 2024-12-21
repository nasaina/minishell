/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:16:46 by maandria          #+#    #+#             */
/*   Updated: 2024/12/21 14:40:41 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	path_error(t_ast *ast)
{
	ft_putstr_fd(ast->cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*check_path(char **pathlist, t_ast *ast)
{
	int		i;
	char	*path;
	char	*command;
	char	*path_tmp;

	i = 0;
	path = NULL;
	command = ft_strjoin("/", ast->cmd->args[0]);
	if (!pathlist)
	{
		free(command);
		return (NULL);
	}
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
	free_tab(pathlist);
	free(command);
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

int	is_command(t_ast *ast)
{
	char	*cmd;

	cmd = ast->cmd->args[0];
	if (access(cmd, X_OK) == 0)
		return (1);
	return (0);
}