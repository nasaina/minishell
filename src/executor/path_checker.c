/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:12:38 by maandria          #+#    #+#             */
/*   Updated: 2024/11/13 16:33:35 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char    **path_list(t_export **export)
{
    t_export *tmp;
    char    *list = NULL;
    char    **pl;

    tmp = *export;
    while (tmp->next)
    {
        if (ft_strncmp(tmp->env, "PATH=", 5) == 0)
        {
            list = tmp->env;
            break ;
        }
        else
            tmp = tmp->next;
    }

    printf("path list : %s\n", list);
    pl = ft_split(list + 5, ':');
    int i = 0;
    while (pl[i])
    {
        printf("%i : %s\n", i, pl[i]);
        i++;
    }
    return (pl);
}