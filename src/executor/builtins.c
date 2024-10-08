/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:15:40 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/08 09:33:22 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_echo(t_chunk *chunks, char **env)
{
	if (!ft_strncmp(chunks->str, "echo", 5))
	{
		chunks = chunks->next;
		if (!chunks)
			return ;
		if (!ft_strncmp(chunks->str, "-n", 3))
		{
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

void	ms_print_export(char *str, char **env)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "env", 4) == 0)
	{
		while (env[i])
		{
			printf("declare -x %s\n", env[i]);
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

void	ms_builtins(t_chunk *chunks, char *str, char **env)
{
	ms_echo(chunks, env);
	ms_pwd(str);
	ms_env(str, env);
	ms_export(env, chunks);
}
