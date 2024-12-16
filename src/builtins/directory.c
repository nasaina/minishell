/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:55:42 by maandria          #+#    #+#             */
/*   Updated: 2024/12/16 15:40:37 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void	ms_pwd(t_ast *ast)
{
	char	pwd[PATH_MAX];

	if (!ft_strncmp(ast->cmd->args[0], "pwd", 4))
	{
		if (getcwd(pwd, PATH_MAX) != NULL)
			printf("%s\n", pwd);
		else
			perror("getcwd");
	}
}

char	*get_home(char **env)
{
	int		i;
	char	*old;
	char	*last;

	i = 0;
	old = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			old = env[i];
			break ;
		}
		else
			i++;
	}
	last = old + 5;
	return (last);
}

char	*get_cd(char *str, char *last_direcotry, char **env)
{
	char	*dir;
	char	cwd[PATH_MAX];

	dir = NULL;
	if (!str)
	{
		dir = get_home(env);
		if (!dir)
			ft_putstr_fd("cd: HOME environment variable not set\n", 2);
	}
	else if (ft_strncmp(str, "-", 2) == 0)
	{
		dir = last_direcotry;
		if (!dir)
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		else if (getcwd(cwd, PATH_MAX) != NULL)
			printf("%s\n", cwd);
	}
	else
		dir = str;
	return (dir);
}

char	*last_dir(char **env)
{
	int		i;
	char	*old;
	char	*last;

	i = 0;
	old = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			old = env[i];
			break ;
		}
		else
			i++;
	}
	last = old + 7;
	return (last);
}

int	get_oldpwd(t_ast *ast,char *dir, char *last_directory)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		if (!chdir(dir))
			last_directory = ft_strdup((const char *)cwd);
		else
		{
			ft_putstr_fd("cd: ", 1);
			perror(ast->cmd->args[1]);
			return (1);
		}
	}
	else
	{
		perror("getcwd");
		return (1);
	}
	return (0);
}

int	ms_cd(t_ast *ast, char **env)
{
	char	*dir;
	char	*last_directory;

	last_directory = NULL;
	if (!last_directory)
		last_directory = last_dir(env);
	if (ft_strcmp(ast->cmd->args[0], "cd") == 0)
	{
		dir = get_cd(ast->cmd->args[1], last_directory, env);
		return(get_oldpwd(ast, dir, last_directory));
	}
	return (0);
}
