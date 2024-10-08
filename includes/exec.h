/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:31:44 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/08 15:03:01 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_export
{
	char			*env;
	struct s_export	*next;
}	t_export;

void	export_back(t_export **export, char *str);
void	ms_printenv(char **env);
int		ft_strcmp(char *s1, char *s2);

#endif