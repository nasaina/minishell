/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:15:40 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 07:46:19 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ms_env(char **str, t_env *env)
{
	if (ft_strncmp(str[0], "env", 4) == 0)
	{
		if (!env)
		{
			printf("\n");
			return (1);
		}
		while (env)
		{
			printf("%s\n", env->env);
			env = env->next;
		}
	}
	return (0);
}

int	ms_builtins(t_ast *ast, t_env *env)
{
	int	status;

	status = -1;
	if (ft_strcmp(ast->cmd->args[0], "cd") == 0)
		return (ms_cd(ast, env));	
	status = ms_echo(ast->cmd);
	status = ms_pwd(ast);
	status =  ms_env(ast->cmd->args, env);
	status = ms_printenv(ast, env);
	status = ms_unset(&env, ast->cmd->args);
	return (status);
}
