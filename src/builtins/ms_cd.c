/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:55:42 by maandria          #+#    #+#             */
/*   Updated: 2024/12/24 08:50:28 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_home(t_env *env)
{
	t_env	*tmp;
	char	*home;
	char	*addhome;

	tmp = env;
	home = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->env, "HOME=", 5) == 0)
		{
			home = tmp->env;
			break ;
		}
		else
			tmp = tmp->next;
	}
	if (!home)
		return (NULL);
	addhome = ft_strdup(home + 5);
	return (addhome);
}

char	*get_cd(char *str, char *last_direcotry, t_env *env)
{
	char	*dir;
	char	cwd[PATH_MAX];

	dir = NULL;
	if (!str)
	{
		dir = get_home(env);
		if (!dir)
		{
			ft_putstr_fd("cd: HOME environment variable not set\n", 2);
			return (NULL);
		}
	}
	else if (str && ft_strncmp(str, "-", 2) == 0)
	{
		dir = join_free(NULL, last_direcotry, 1);
		if (!dir)
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		else if (getcwd(cwd, PATH_MAX) != NULL)
		{
			printf("%s\n", last_direcotry);
			free(last_direcotry);
		}
	}
	else
		dir = ft_strdup(str);
	free(last_direcotry);
	return (dir);
}

char	*last_dir(t_env *env)
{
	t_env	*tmp;
	char	*old;
	char	*last;	

	tmp = env;
	old = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->env, "OLDPWD=", 7) == 0)
		{
			old = tmp->env;
			break ;
		}
		else
			tmp = tmp->next;
	}
	if (old)
		last = ft_strdup(old + 7);
	else
		return (NULL);
	return (last);
}

int	get_oldpwd(t_ast *ast, char *dir, char *last_directory, t_env *env)
{
	char	cwd[PATH_MAX];
	char	*new_dir;

	(void)last_directory;
	new_dir = NULL;
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		if (!chdir(dir))
		{
			free(dir);
			change_env_oldpwd(env, cwd);
		}
		else
		{
			ft_putstr_fd("cd: ", 1);
			free(dir);
			perror(ast->cmd->args[1]);
			return (1);
		}
		change_env_pwd(env);
	}
	else
	{
		free(dir);
		perror("getcwd");
		return (1);
	}
	return (0);
}

int	ms_cd(t_ast *ast, t_env *env)
{
	char	*dir;
	char	*last_directory;

	last_directory = last_dir(env);
	if (ft_strcmp(ast->cmd->args[0], "cd") == 0)
	{
		if (check_args(ast))
		{
			ft_putstr_fd("cd: too many arguments\n", 2);
			free(last_directory);
			return (1);
		}
		dir = get_cd(ast->cmd->args[1], last_directory, env);
		return (get_oldpwd(ast, dir, NULL, env));
	}
	free(last_directory);
	return (0);
}