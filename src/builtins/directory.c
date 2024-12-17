/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:55:42 by maandria          #+#    #+#             */
/*   Updated: 2024/12/17 13:21:19 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_home(t_export *export)
{
	t_export	*tmp;
	char		*home;
	char		*addhome;

	tmp = export;
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

int	check_args(t_ast *ast)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ast->cmd->args;
	while (tmp[i])
		i++;
	if (i > 2)
		return (1);
	return (0);
}

char	*get_cd(char *str, char *last_direcotry, t_export *export)
{
	char	*dir;
	char	cwd[PATH_MAX];

	dir = NULL;
	if (!str)
	{
		dir = get_home(export);
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

char	*last_dir(t_export *export)
{
	t_export	*tmp;
	char		*old;
	char		*last;

	tmp = export;
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
	last = ft_strdup(old + 7);
	printf("#### %s ####\n", last);
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

int	ms_cd(t_ast *ast, t_export *export)
{
	char	*dir;
	char	*last_directory;

	last_directory = NULL;
	if (!last_directory)
		last_directory = last_dir(export);
	if (ft_strcmp(ast->cmd->args[0], "cd") == 0)
	{
		dir = get_cd(ast->cmd->args[1], last_directory, export);
		return(get_oldpwd(ast, dir, last_directory));
	}
	return (0);
}
