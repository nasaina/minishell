/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:31:44 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/10 13:22:34 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <minishell.h>
# include <expander.h>

typedef struct s_export
{
	char			*env;
	struct s_export	*next;
}	t_export;

int			ft_strcmp(char *s1, char *s2);
t_export	*ms_envcpy(char **env);
void		export_back(t_export **export, char *str);
void		free_export(t_export *export);
char    	**path_list(char **env);

#endif
