/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:24:31 by maandria          #+#    #+#             */
/*   Updated: 2024/12/24 15:58:10 by nandrian         ###   ########.fr       */
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

int	check_ifexist(t_env *env, char *str)
{
	t_env	*tmp;
	char	*name;

	tmp = env;
	while (tmp)
	{
		name = env_name(tmp->env);
		if (!ft_strcmp(name, str))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	change_env_pwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*new_dir;

	if (!check_ifexist(env, "PWD"))
		return ;
	getcwd(cwd, PATH_MAX);
	is_double(&env, "PWD");
	new_dir = ft_strjoin("PWD=", cwd);
	env_back(&env, new_dir);
	free(new_dir);
}

void	change_env_oldpwd(t_env *env, char *cwd)
{
	char	*new_dir;

	if (!check_ifexist(env, "OLDPWD"))
		return ;
	new_dir = NULL;
	is_double(&env, "OLDPWD");
	new_dir = ft_strjoin("OLDPWD=", cwd);
	env_back(&env, new_dir);
	free(new_dir);
}
