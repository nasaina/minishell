/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:55:42 by maandria          #+#    #+#             */
/*   Updated: 2024/10/08 08:35:11 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_pwd(char *str)
{
	char	*pwd;

	if (!ft_strncmp(str, "pwd", 4))
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
	}
}

void	ms_cd(char *str)
{
	chdir(str);
}
