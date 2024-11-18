/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:17:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/11/18 17:02:16 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <minishell.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	ft_strlen(char *str)
{
	if (!str)
		return (0);
	int i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
	
}

char	*strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int	is_variable(char *str)
{
	int	i;

	i = 0;
	if (str[i] == 39)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	no_quote(char *str, int i)
{
	int		count;

	count = 0;
	while (str[i] != 34 && str[i] != 39 && str[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	quote_simple(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i] && str[i] != '\'')
	{
		i++;
		count++;
	}
	return (count);
}

int	quote_double(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i] && str[i] != '\"')
	{
		i++;
		count++;
	}
	return (count);
}

char	*cpy(char *str, int count, int *i)
{
	char	*new;
	int		j;

	j = 0;
	new = malloc(count + 1);
	while (j < count)
	{
		new[j] = str[*i];
		j++;
		*i += 1;
	}
	new[j] = 0;
	return (new);
}

char	*expanded(char *str)
{
	int		i;
	int		count;
	char	*new;
	char	*out;

	i = 0;
	out = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			count = quote_simple(str, i);
			new = cpy(str, count, &i);
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			count = quote_double(str, i);
			new = cpy(str, count, &i);
			i++;
		}
		else
		{
			count = no_quote(str, i);
			new = cpy(str, count, &i);
		}
		out = strjoin(out, new);
	}
	return (out);
}

char	*get_var_name(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*name;

	i = 0;
	len = 0;
	while (str[i] != '$')
		i++;
	i++;
	j = i;
	while (str[i] != 32 && str[i])
	{
		i++;
		len++;
	}
	name = malloc(len + 1);
	i = 0;
	while (i < len)
		name[i++] = str[j++];
	name[i] = 0;
	return (name);
}

int	main()
{

	char *str = "this is a \"$te\'gt\"in\'the \" club\'";
	// str = jump_quote(str);
	printf("%s\n", expanded(str));
}

// char	*expanded_str(char *str, t_export *export)
// {
// 	int	i;

// 	i = 0;

	
// }

