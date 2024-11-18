/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:04:22 by nandrian          #+#    #+#             */
/*   Updated: 2024/11/18 12:52:06 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
			if (str[i] == 34)
			{
				i++;
				count++;
				while (str[i] && str[i] != 34)
				{
					if (str[i] == '\\' && str[i + 1] == 34)
					{
						i += 2;
						count += 2;
					}
					i++;
					count++;
				}
			}
		}
		i++;
	}
	return (count);
}
