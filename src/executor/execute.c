/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:51:47 by nandrian          #+#    #+#             */
/*   Updated: 2024/11/18 13:17:09 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

const char	**init_builtins(void)
{
	static const char	*builtins[] = {
	"cd",
	"echo",
	"env",
	"exit",
	"export",
	"pwd",
	"unset",
	NULL
	};
	return (builtins);
}

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
	tmp = "/";
	command = ft_strjoin(tmp, ast->cmd->args[0]);

	while (pathlist[i])
	{
		if (access(ft_strjoin(pathlist[i], command), F_OK) == 0)
		{
			path = ft_strjoin(pathlist[i], tmp);
			path  = ft_strjoin(path, ast->cmd->args[0]);
			return (path);
		}
		else
			i++;
	}
	perror(command);
	return (NULL);
}

void	exec_cmd(t_ast *ast, t_export *export, char **env)
{
	pid_t	pid;
	int	status;
	char	**pathlist;
	char	*path;

	pathlist = path_list(&export);
	path = check_path(pathlist, ast);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (execve(path, &ast->cmd->args[0], env) == -1)
		{
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
