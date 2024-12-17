/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:24:31 by maandria          #+#    #+#             */
/*   Updated: 2024/12/17 14:37:29 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ms_pwd(t_ast *ast)
{
	char	pwd[PATH_MAX];

	(void)pwd;
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
