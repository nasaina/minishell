/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 09:21:15 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 09:41:59 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_dir_old(char *last_directory)
{
	char	*dir;

	dir = ft_strdup(last_directory);
	ft_putendl_fd(dir, 1);
	return (dir);
}

int	cd_error(char *dir, t_ast *ast)
{
	ft_putstr_fd("minishell: cd: ", 1);
	free(dir);
	perror(ast->cmd->args[1]);
	return (1);
}
