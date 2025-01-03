/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:48:51 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/22 11:25:58 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_str(char *s1, char *s2, int status)
{
	if (status == 1)
		free(s2);
	else if (status == 0)
		free(s1);
	else if (status == 2)
	{
		free(s1);
		free(s2);
	}
}

char	*join_free(char *s1, char *s2, int status)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free_str(s1, s2, status);
	return (str);
}
