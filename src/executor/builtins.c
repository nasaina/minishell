/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:15:40 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/09 11:19:37 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_echoflag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == 45)
	{
		while (str[i])
		{
			if (str[i] != 110)
				return (0);
			i++;
		}
	}
	return (1);
}

void	ms_echo(t_chunk *chunks, char **env)
{
	if (!ft_strncmp(chunks->str, "echo", 5))
	{
		chunks = chunks->next;
		if (!chunks)
			return ;
		if (is_echoflag(chunks->str) && chunks->next)
		{
			while (is_echoflag(chunks->str) && chunks->next)
				chunks = chunks->next;
			while (chunks)
			{
				printf("%s", expander(chunks->str, env));
				chunks = chunks->next;
				if (chunks)
					printf(" ");
			}
		}
		else
		{
			while (chunks)
			{
				printf("%s", expander(chunks->str, env));
				chunks = chunks->next;
				if (chunks)
					printf(" ");
			}
			printf("\n");
		}
	}
}

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

void	ms_builtins(t_export *export, t_chunk *chunks, char *str, char **env)
{
	ms_echo(chunks, env);
	ms_pwd(str);
	ms_env(str, env);
	ms_printenv(export, chunks);
	ms_unset(&export, chunks);
}
