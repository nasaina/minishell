/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:56:23 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 11:52:57 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	restart_result(char **result, char **split)
{
	if (*result)
		free(*result);
	*result = NULL;
	free_tab(split);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i])
		return (0);
	return (s1[i] - s2[i]);
}
