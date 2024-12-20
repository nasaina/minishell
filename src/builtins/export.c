/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:58:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 08:19:12 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	add_input(t_env *env, int i, char **args)
{
	t_env	*tmp;
	char	*name;

	if (args[i])
	{
		while (args[i])
		{
			name = NULL;
			tmp = env;
			name = env_name(args[i]);
			if (check_input(args, i, name))
			{
				i++;
				continue ;
			}
			is_double(&tmp, name);
			free(name);
			env_back(&tmp, args[i]);
			i++;
		}
	}
	else
		print_env(env);
	return (check_status(args));
}

int	ms_printenv(t_ast *ast, t_env *env)
{
	int			i;
	char		*name;
	char		**args;

	i = 0;
	name = NULL;
	args = ast->cmd->args;
	if (!ft_strcmp(args[i], "export"))
	{
		i++;
		if (add_input(env, i, args))
			return (1);
	}
	return (0);
}
