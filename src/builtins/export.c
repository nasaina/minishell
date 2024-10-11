/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:58:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/11 13:15:00 by nandrian         ###   ########.fr       */
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

void	ms_printenv(t_export *export, t_chunk *chunks)
{
	int	i;

	if (!ft_strcmp(chunks->str, "export"))
	{
		chunks = chunks->next;
		if (chunks)
		{
			while (chunks)
			{
				export_back(&export, chunks->str);
				chunks = chunks->next;
			}
		}
		else
		{
			sort_env(&export);
			while (export)
			{
				i = 0;
				printf("declare -x ");
				ft_printenv(export, &i);
				export = export->next;
			}
		}
	}
}
