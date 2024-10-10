/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:31:44 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/10 21:33:56 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <minishell.h>

typedef struct s_export
{
	char			*env;
	struct s_export	*next;
}	t_export;

int			ft_strcmp(char *s1, char *s2);
t_export	*ms_getenv(char **env);
void		ms_unset(t_export **export, t_chunk *chunks);
void		export_back(t_export **export, char *str);
void		ms_printenv(t_export *export, t_chunk *chunks);
#endif
