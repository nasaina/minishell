/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:55:42 by maandria          #+#    #+#             */
/*   Updated: 2024/10/10 20:36:42 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_pwd(t_cmd *cmd)
{
	char	*pwd;

	if (!ft_strncmp(cmd->args[0], "pwd", 4))
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
	}
}

void	ms_cd(char *str)
{
	chdir(str);
}
