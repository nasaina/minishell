/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:19:54 by maandria          #+#    #+#             */
/*   Updated: 2024/12/22 10:29:14 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_fork(t_ast *ast, t_env *env, char *path)
{
	if (ast->cmd->redir)
			do_redir(ast);
		if (ast->cmd->args && ast->cmd->args[0])
			exec_fork(ast, path, env);
}
