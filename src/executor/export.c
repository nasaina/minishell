/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:58:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/08 15:54:00 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_export	*ms_getenv(char **env)
{
	t_export	*export;
	int			i;

	i = 0;
	export = NULL;
	while (env[i])
	{
		export_back(&export, env[i]);
		i++;
	}
	return (export);
}

void	sort_env(t_export **export)
{
	t_export	*exp_tmp;
	char		*tmp;

	exp_tmp = *export;
	while (exp_tmp->next)
	{
		if (ft_strcmp(exp_tmp->env, exp_tmp->next->env) > 0)
		{
			tmp = exp_tmp->env;
			exp_tmp->env = exp_tmp->next->env;
			exp_tmp->next->env = tmp;
			exp_tmp = *export;
		}
		else
			exp_tmp = exp_tmp->next;	
	}
}

void	ms_printenv(char **env)
{
	t_export	*export;
	int			i;

	export = ms_getenv(env);
	sort_env(&export);
	while (export)
	{
		i = 0;
		printf("declare -x ");
		while (export->env[i] != 61)
		{
			printf("%c", export->env[i]);
			i++;
		}
		if (export->env[i] == 61)
		{
			printf("%c", export->env[i]);
			i++;
		}
		printf("\"");
		while (export->env[i])
		{
			printf("%c", export->env[i]);
			i++;
		}
		printf("\"\n");
		export = export->next;
	}
}
