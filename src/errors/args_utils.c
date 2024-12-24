/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:41:49 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 15:28:27 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_error(char *str)
{
	if (!check_redirection(str))
	{
		free(str);
		return (1);
	}
	return (0);
}

void	ignore_args(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
}

char	*ft_readline(void)
{
	char	*str;

	str = NULL;
	str = readline(">  ");
	if (str != NULL && str[0] != '\0')
	{
		ms_writehistory(str);
		add_history(str);
	}
	return (str);
}

int	is_void(char *str)
{
	int	i;

	i = 0;
	if (str != NULL && str[i] == '\0')
		return (1);
	else if (str != NULL && (str[i] == 32 || str[i] == '\t'))
	{
		while ((str[i] == 32 || str[i] == '\t') && str[i])
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
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
