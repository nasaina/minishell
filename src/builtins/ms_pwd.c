/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:24:31 by maandria          #+#    #+#             */
/*   Updated: 2024/12/24 08:08:18 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ms_pwd(t_ast *ast)
{
	char	pwd[PATH_MAX];

	if (!ft_strncmp(ast->cmd->args[0], "pwd", 4))
	{
		if (getcwd(pwd, PATH_MAX) != NULL)
			printf("%s\n", pwd);
		else
		{
			perror("getcwd");
			return (1);
		}
	}
	return (0);
}

void	change_env_pwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*new_dir;

	getcwd(cwd, PATH_MAX);
	is_double(&env, "PWD");
	new_dir = ft_strjoin("PWD=", cwd);
	env_back(&env, new_dir);
	free(new_dir);
}

void	change_env_oldpwd(t_env *env, char *cwd)
{
	char	*new_dir;

	new_dir = NULL;
	is_double(&env, "OLDPWD");
	new_dir = ft_strjoin("OLDPWD=", cwd);
	env_back(&env, new_dir);
	free(new_dir);
}
