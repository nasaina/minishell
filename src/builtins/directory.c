/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:55:42 by maandria          #+#    #+#             */
/*   Updated: 2024/12/10 11:33:58 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*last_directory = NULL;

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

char	*get_cd(char *str)
{
	char	*dir;

	dir = NULL;
	if (!str)
	{
		dir = getenv("HOME");
		if (!dir)
			ft_putstr_fd("cd: HOME environment variable not set\n", 2);
	}
	else if (ft_strncmp(str, "-", 2) == 0)
	{
		dir = last_directory;

		if (!dir)
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
	}
	else
		dir = str;
	return (dir);
}

void	ms_cd(t_ast *ast)
{
	char	*dir;
	char	cwd[PATH_MAX];

	if (ft_strcmp(ast->cmd->args[0], "cd") == 0)
	{
		dir = get_cd(ast->cmd->args[1]);
		if (getcwd(cwd, PATH_MAX) != NULL)
		{
			if (chdir(dir) == 0)
			{
				free(last_directory);
				last_directory = ft_strdup((const char *)cwd); 
			}
			else if (!ft_strcmp("(null)", dir))
				printf("\n");
			else
				perror("cd");
		}
		else
			perror("getcwd");
	}
}
