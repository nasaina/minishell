/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:51:47 by nandrian          #+#    #+#             */
/*   Updated: 2024/11/20 11:18:33 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	isbuiltin(t_ast *ast)
{
	const char	**builtins;
	int			i;

	builtins = init_builtins(); 
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(ast->cmd->args[0], (char *)builtins[i]) == 0)
			return (1);
		else
			i++;
	}
	return (0);
}

char	*check_path(char **pathlist, t_ast *ast)
{
	int	i;
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
	perror(ast->cmd->args[0]);
	return (NULL);
}

char	*check_access(t_ast *ast)
{
	char	*path;
	char	*command;

	command = ast->cmd->args[0];

	if (access(command, F_OK) == 0)
	{
		path  = ast->cmd->args[0];
		return (path);
	}
	perror(command);
	return (NULL);
}

void	exec_cmd(t_ast *ast, t_export *export, char **env)
{
	pid_t	pid;
	int	status;
	char	*path;

	if (ast->cmd->args[0][0] == '/' || ast->cmd->args[0][0] == '.')
		path = check_access(ast);
	else
		path = check_path(path_list(&export), ast);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (execve(path, &ast->cmd->args[0], env) == -1)
		{
				if (path == NULL)
					exit (EXIT_FAILURE);
				perror("execve");
		}
		exit (EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}

void	check_cmd(t_ast *ast, t_export *export, t_expander *expander, char *str, char **env)
{
	if (isbuiltin(ast))
	{
		printf("\n*** usain built ***\n");
		ms_builtins(ast, export, expander, str, env);
	}
	else
		exec_cmd(ast, export, env);
}
