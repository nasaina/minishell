/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:15:40 by nandrian          #+#    #+#             */
/*   Updated: 2024/11/18 14:46:19 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_env(char **env, int *i, int *j)
{
	while (env[*i][*j] != 61)
	{
		printf("%c", env[*i][*j]);
		*j += 1;
	}
	if (env[*i][*j] == 61)
	{
		printf("%c", env[*i][*j]);
		*j += 1;
	}
	printf("\"");
	while (env[*i][*j])
	{
		printf("%c", env[*i][*j]);
		*j += 1;
	}
}

void	ms_print_export(char *str, char **env)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strncmp(str, "env", 4) == 0)
	{
		while (env[i])
		{
			j = 0;
			printf("declare -x ");
			while (env[i][j])
			{
				print_env(env, &i, &j);
				printf("\"\n");
			}
			i++;
		}
	}
}

void	ms_export(char **env, t_chunk *chunks)
{
	int	i;

	i = 0;
	if (!ft_strncmp(chunks->str, "export", 7))
	{
		while (env[i])
			i++;
		chunks = chunks->next;
		if (chunks)
		{
			printf("OK\n");
		}
		else
			ms_print_export("env", env);
	}
}


void	ms_env(char *str, char **env)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "env", 4) == 0)
	{
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
}

void	ms_builtins(t_ast *ast, t_export *export, t_expander *expander, char *str, char **env)
{
	ms_echo(expander);
	ms_pwd(ast);
	ms_env(str, env);
	ms_cd(ast);
	ms_printenv(ast, export);
	ms_unset(&export, expander);
}
