/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:12:38 by maandria          #+#    #+#             */
/*   Updated: 2024/12/03 16:31:47 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char    **path_list(char **env)
{
	int		i;
    char    *list = NULL;
    char    **pl;

	i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
        {
            list = env[i];
            break ;
        }
        else
            i++;
    }

    pl = ft_split(list + 5, ':');
    return (pl);
}