/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:04:22 by nandrian          #+#    #+#             */
/*   Updated: 2024/11/18 13:13:49 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	double_quote(char *str, int *i, int *count)
{
	if (str[*i] == 39)
	{
		*i += 1;
		*count += 1;
		while (str[*i] && str[*i] != 39)
		{
			*i += 1;
			*count += 1;
		}
	}
}

void	single_quote(char *str, int *i, int *count)
{
	if (str[*i] == 34)
	{
		*i += 1;
		*count += 1;
		while (str[*i] && str[*i] != 34)
		{
			*i += 1;
			*count += 1;
		}
	}
}

int qword_len(char *str, int i)
{
	int count;

	count = 0;
	while (str[i] != 32 && str[i] && is_word(str[i]))
	{
		if (str[i] == 32)
		{
			count = 0;
			i++;
		}
		else
		{
			count++;
			single_quote(str, &i, &count);
			double_quote(str, &i, &count);
		}
		i++;
	}
	return (count);
}
