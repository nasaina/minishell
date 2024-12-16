/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:15:40 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/13 15:51:53 by maandria         ###   ########.fr       */
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


void	ms_env(char **str, t_export *export)
{
	if (ft_strncmp(str[0], "env", 4) == 0)
	{
		while (export)
		{
			printf("%s\n", export->env);
			export = export->next;
		}
	}
}

int	ms_builtins(t_ast *ast, t_export *export, char **env)
{
	(void)export;
	return (ms_cd(ast, env));
	/* ms_echo(ast->cmd);
	ms_pwd(ast);
	ms_env(ast->cmd->args, export);
	ms_printenv(ast, export);
	ms_unset(&export, ast->cmd->args); */
}
