/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:58:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 07:54:35 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*env_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(i + 1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = 0;
	return (name);
}

int	double_input(char **str, int i, char *args)
{
	char	*name;

	i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		name = env_name(str[i]);
		if (!ft_strcmp(args, name))
		{
			free(name);
			return (1);
		}
		i++;
	}
	free(name);
	return (0);
}

int	is_invalidname(char *str)
{
	if (!isalpha(str[0]) && str[0] != '_')
		return (1);
	return (0);
}

int	check_status(char **args)
{
	int		i;
	char	*name;

	i = 0;
	while (args[i])
	{
		name = NULL;
		name = env_name(args[i]);
		if (is_invalidname(name))
		{
			free(name);
			return (1);
		}
		free(name);
		i++;
	}
	return (0);
}

int	add_input(t_env *env, int i, char **args)
{
	t_env	*tmp;
	char		*name;

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
