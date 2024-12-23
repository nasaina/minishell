/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:15:40 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/23 16:04:03 by nandrian         ###   ########.fr       */
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

char	**init_builtins(void)
{
	static char	*builtins[8];

	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "env";
	builtins[3] = "exit";
	builtins[4] = "export";
	builtins[5] = "pwd";
	builtins[6] = "unset";
	builtins[7] = NULL;
	return (builtins);
}

int	ms_builtins(t_ast *ast, t_env *env, int in, int out)
{
	int	status;

	status = -1;
	status = ms_cd(ast, env);
	status = ms_echo(ast->cmd);
	status = ms_pwd(ast);
	status = ms_env(ast->cmd->args, env);
	status = ms_printenv(ast, env);
	status = ms_unset(&env, ast->cmd->args);
	if (ast && handle_exit(ast, env, in, out))
		return (1);
	return (status);
}
