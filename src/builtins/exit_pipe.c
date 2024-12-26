/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:05:08 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 12:15:49 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exit_pipe(t_ast *ast)
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
		return (status);
	}
	return (0);
}

int	handle_exit_pipe(t_ast *ast)
{
	if (ast->cmd->args[0]
		&& !ft_strcmp(ast->cmd->args[0], "exit") && !ast->cmd->args[1])
		return (exit_status());
	else if (!ft_strcmp(ast->cmd->args[0], "exit") && ast->cmd->args[1])
	{
		if (str_isnum(ast->cmd->args[1]))
			return (2);
		if (ft_exit_pipe(ast))
			return (1);
	}
	return (0);
}
