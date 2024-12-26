/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:16:46 by maandria          #+#    #+#             */
/*   Updated: 2024/12/26 09:15:59 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	path_error(t_ast *ast, char *str)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(ast->cmd->args[0], 2);
	ft_putstr_fd(str, 2);
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

char	*check_path(char **pathlist, t_ast *ast, int *status)
{
	char		*path;
	char		*command;

	path = NULL;
	command = ft_strjoin("/", ast->cmd->args[0]);
	if (!pathlist)
	{
		free(command);
		return (NULL);
	}
	path = takepath_and_free(command, pathlist);
	if (path)
		return (path);
	free_tab(pathlist);
	free(command);
	if (ast->cmd->args[0] != NULL)
		stat_isdir(ast, status);
	return (path);
}

char	*check_access(t_ast *ast)
{
	char	*path;
	char	*command;

	command = ast->cmd->args[0];
	path = NULL;
	if (access(command, F_OK) == 0)
	{
		path = ft_strdup(ast->cmd->args[0]);
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
