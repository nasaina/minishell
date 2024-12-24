/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:45:00 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 09:49:14 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_tab(char c)
{
	if (c == 32 || c == '\t')
		return (1);
	return (0);
}

static int	ft_countw(char const *s)
{
	int	i;
	int	wrd;

	i = 0;
	wrd = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && is_tab(s[i]))
			i++;
		if (s[i] != '\0')
		{
			wrd++;
		}
		while (s[i] != '\0' && !is_tab(s[i]))
			i++;
	}
	return (wrd);
}

static int	ft_splitword(char const *s)
{
	int	i;

	i = 0;
	while (s[i] && !is_tab(s[i]))
		i++;
	return (i);
}

static char	*ft_tab(char const *str)
{
	char	*tab;
	int		i;
	int		len_t;

	i = 0;
	len_t = ft_splitword(str);
	tab = malloc(sizeof(char) * (len_t + 1));
	if (!tab)
		return (NULL);
	while (i < len_t)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split_tab(char const *s)
{
	int		i;
	char	**str;
	int		size;

	if (!s)
		return (NULL);
	size = ft_countw(s);
	str = malloc(sizeof(char *) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s != '\0' && is_tab(*s))
			s++;
		if (*s != '\0')
		{
			str[i] = ft_tab(s);
			i++;
		}
		while (*s != '\0' && !is_tab(*s))
			s++;
	}
	str[i] = 0;
	return (str);
}
