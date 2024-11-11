/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:51:47 by nandrian          #+#    #+#             */
/*   Updated: 2024/11/11 10:57:06 by maandria         ###   ########.fr       */
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

void	exec_cmd(t_ast *ast)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (execve(ast->cmd->args[0], &ast->cmd->args[0], NULL ) == -1)
			perror("execve");
		exit (EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}

void	check_cmd(t_ast *ast, t_export *export, t_expander *expander, char *str, char **env)
{
	if (isbuiltin(ast))
		ms_builtins(ast, export, expander, str, env);
	else
		exec_cmd(ast);
}
