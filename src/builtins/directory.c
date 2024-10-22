/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:55:42 by maandria          #+#    #+#             */
/*   Updated: 2024/10/21 14:58:32 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*last_directory = NULL;

void	ms_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = NULL;
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
	{
		if (getcwd(pwd, sizeof(pwd)) != NULL)
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

void	ms_cd(char *str)
{
	char	*dir;
	char	cwd[1024];

	dir = get_cd(str);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (chdir(dir) == 0)
		{
			free(last_directory);
			last_directory = ft_strdup((const char *)cwd); 
		}
		else
			perror("cd");
	}
	else
		perror("getcwd");
}
