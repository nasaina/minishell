/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:55:34 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/17 13:53:29 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_export	*ms_envcpy(char **env)
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

void	ft_printenv(t_export *export, int *i)
{
	while (export->env[*i] != 61 && export->env[*i])
	{
		printf("%c", export->env[*i]);
		*i += 1;
	}
	if (export->env[*i] == 61)
	{
		printf("%c", export->env[*i]);
		*i += 1;
		if (export->env[*i] != 34)
			printf("\"");
	}
	else
	{
		printf("\n");
		return ;
	}
	while (export->env[*i])
	{
		printf("%c", export->env[*i]);
		*i += 1;
	}
	if (export->env[*i - 1] != 34)
		printf("\"\n");
}

void	print_export(t_export *export)
{
	int	j;

	sort_env(&export);
	while (export)
	{
		j = 0;
		printf("declare -x ");
		ft_printenv(export, &j);
		export = export->next;
	}
}

void	is_double(t_export **export, char *name)
{
	t_export	*tmp;
	char		*str;

	tmp = *export;
	str = NULL;
	while (tmp && tmp->next)
	{
		str = export_name(tmp->next->env);
		if (!ft_strcmp(name, str))
			remove_env(export, name);
		free(str);
		tmp = tmp->next;
	}
}
