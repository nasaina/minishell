/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:31:44 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 07:43:01 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <minishell.h>
# include <expander.h>

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}	t_env;

int			ft_strcmp(char *s1, char *s2);
t_env	*ms_envcpy(char **env);
void		env_back(t_env **env, char *str);
void		free_env(t_env *env);
char		**path_list(char **env);

#endif