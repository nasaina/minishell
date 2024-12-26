/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:17:19 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 14:40:50 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_dup(int in, int out, int print)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	unlink("/tmp/.ms_status");
	if (print == 1)
		ft_putstr_fd("exit\n", 1);
	close(in);
	close(out);
}

int	ft_exit(t_ast *ast, t_env *env, int in, int out)
{
	int			i;
	int			status;

	i = 0;
	while (ast->cmd->args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("minishell : exit : too many arguments", 2);
		return (1);
	}
	else if (i == 2)
	{
		status = ft_atoi(ast->cmd->args[1]);
		free_env(env);
		free_ast(ast);
		close_dup(in, out, 1);
		exit(status);
	}
	return (0);
}

int	handle_exit(t_ast *ast, t_env *env, int in, int out)
{
	int	status;

	status = -1;
	if (ast->cmd->args[0]
		&& !ft_strcmp(ast->cmd->args[0], "exit") && !ast->cmd->args[1])
	{
		free_env(env);
		free_ast(ast);
		status = exit_status();
		close_dup(in, out, 1);
		exit(status);
	}
	else if (!ft_strcmp(ast->cmd->args[0], "exit") && ast->cmd->args[1])
	{
		if (str_isnum(ast->cmd->args[1]))
		{
			free_env(env);
			free_ast(ast);
			close_dup(in, out, 0);
			exit(2);
		}
		if (ft_exit(ast, env, in, out))
			return (1);
	}
	return (0);
}
