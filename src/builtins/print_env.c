/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:55:34 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 07:57:59 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*ms_envcpy(char **envp)
{
	t_env	*env;
	int			i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		env_back(&env, envp[i]);
		i++;
	}
	return (env);
}

void	sort_env(t_env **env)
{
	t_env	*exp_tmp;
	char		*tmp;

	exp_tmp = *env;
	while (exp_tmp->next)
	{
		if (ft_strcmp(exp_tmp->env, exp_tmp->next->env) > 0)
		{
			tmp = exp_tmp->env;
			exp_tmp->env = exp_tmp->next->env;
			exp_tmp->next->env = tmp;
			exp_tmp = *env;
		}
		else
			exp_tmp = exp_tmp->next;
	}
}

void	ft_printenv(t_env *env, int *i)
{
	while (env->env[*i] != 61 && env->env[*i])
	{
		printf("%c", env->env[*i]);
		*i += 1;
	}
	if (env->env[*i] == 61)
	{
		printf("%c", env->env[*i]);
		*i += 1;
		if (env->env[*i] != 34)
			printf("\"");
	}
	else
	{
		printf("\n");
		return ;
	}
	while (env->env[*i])
	{
		printf("%c", env->env[*i]);
		*i += 1;
	}
	if (env->env[*i - 1] != 34)
		printf("\"\n");
}

void	print_env(t_env *env)
{
	int	j;

	sort_env(&env);
	while (env)
	{
		j = 0;
		printf("declare -x ");
		ft_printenv(env, &j);
		env = env->next;
	}
}

void	is_double(t_env **env, char *name)
{
	t_env	*tmp;
	char		*str;

	tmp = *env;
	str = NULL;
	while (tmp && tmp->next)
	{
		str = env_name(tmp->next->env);
		if (!ft_strcmp(name, str))
			remove_env(env, name);
		free(str);
		tmp = tmp->next;
	}
}
