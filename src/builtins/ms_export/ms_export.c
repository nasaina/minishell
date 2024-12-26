/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:58:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 08:39:21 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_input(char **args, int i, char *name)
{
	if (is_invalidname(name))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(args[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (double_input(args, i, name))
		return (1);
	return (0);
}

int	export_pwd(t_env **env, char *str, int *i)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	pwd = NULL;
	getcwd(cwd, PATH_MAX);
	pwd = ft_strjoin("PWD=", cwd);
	is_double(env, "PWD");
	env_back(env, pwd);
	free(pwd);
	*i += 1;
	if (!str)
		return (1);
	return (0);
}

int	insert_env(t_env **env, char **args, int *i)
{
	char	*name;

	name = NULL;
	name = env_name(args[*i]);
	if (check_input(args, *i, name))
	{
		*i += 1;
		free(name);
		return (1);
	}
	is_double(env, name);
	free(name);
	env_back(env, args[*i]);
	return (0);
}

int	add_input(t_env *env, int i, char **args)
{
	t_env	*tmp;

	if (args[i])
	{
		while (args[i])
		{
			tmp = env;
			if (!ft_strcmp("PWD", args[i]))
			{
				if (export_pwd(&tmp, args[i], &i))
					break ;
			}
			else
			{
				if (insert_env(&tmp, args, &i))
					continue ;
			}
			if (!args[i])
				break ;
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
	char		**args;

	i = 0;
	args = ast->cmd->args;
	if (!ft_strcmp(args[i], "export"))
	{
		i++;
		if (add_input(env, i, args))
			return (1);
	}
	return (0);
}
