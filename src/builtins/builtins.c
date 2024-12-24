/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:15:40 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 15:40:37 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ignore_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

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
			if (ignore_str(env->env))
			{
				env = env->next;
				if (env == NULL)
					break ;
			}
			if (env)
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
	if (ft_strcmp(ast->cmd->args[0], "cd") == 0)
		status = ms_cd(ast, env);
	else if (ft_strcmp(ast->cmd->args[0], "echo") == 0)
		status = ms_echo(ast->cmd);
	else if (ft_strcmp(ast->cmd->args[0], "pwd") == 0)
		status = ms_pwd(ast);
	else if (ft_strcmp(ast->cmd->args[0], "env") == 0)
		status = ms_env(ast->cmd->args, env);
	else if (ft_strcmp(ast->cmd->args[0], "export") == 0)
		status = ms_printenv(ast, env);
	else if (ft_strcmp(ast->cmd->args[0], "unset") == 0)
		status = ms_unset(&env, ast->cmd->args);
	else if (ft_strcmp(ast->cmd->args[0], "exit") == 0)
	{
		if (ast && handle_exit(ast, env, in, out))
			return (1);
	}
	return (status);
}
