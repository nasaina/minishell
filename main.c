/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:38:26 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/13 15:08:04 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *get_op(char *str, int *i)
{
	char	*wrd;

	while (str[*i] && !isredirection(str[*i]) && str[*i])
		*i += 1;
	if (isredirection(str[*i]) && !isredirection(str[*i + 1]))
	{
		wrd = malloc(sizeof(char));
		wrd[0] = str[*i];
		*i += 1;
	}
	if ((isredirection(str[*i]) && str[*i + 1] == str[*i] && !isredirection(str[*i + 2]))
		|| (str[*i] == '<' && str[*i + 1] == '>'))
	{
		wrd = malloc(2 * sizeof(char));
		wrd[0] = str[*i];
		wrd[1] = str[*i + 1];
		i += 2;
	}
	return (wrd);
}

char *one_word(char *str, int *i)
{
	char	*wrd;
	int		j;

	j = 0;
	if (!str[*i])
		return (NULL);
	while (str[*i] == 32)
		*i += 1;	
	while (str[*i] && !isredirection(str[*i]) && str[*i] != 32)
	{
		j++;
		*i += 1;
	}
	wrd = malloc(j + 1);
	j = 0;
	while (j < *i)
	{
		wrd[j] = str[*i];
		j++;
	}
	wrd[j] = '\0';
	return (wrd);
}

int	count_word(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (str[i + 1])
	{
		if (!isredirection(str[i]) && str[i] != 32)
			i++;
		if (str[i] == 32 && str[i + 1] != 32 && !isredirection(str[i + 1]))
			j++;
		if (isredirection(str[i]) && !isredirection(str[i + 1]))
			j++;
		if (isredirection(str[i]) && str[i + 1] == str[i] && !isredirection(str[i + 2]))
		{
			i++;
			j ++;
		}
		if (str[i] == '<' && str[i + 1] == '>')
			j++;
		i++;
	}	
	return (j);
}

t_chunk *get_chunk(char *str)
{
	t_chunk *chunks;
	char 	*wrd;
	int		i;
	int		j;
	int		wrd_count;

	i = 0;
	j = 0;
	chunks = NULL;
	wrd_count = count_word(str);
	while (j < wrd_count)
	{
		while (str[i] == 32 && str[i])
			i++;
		if (!isredirection(str[i]) && str[i] != 32)
		{
			wrd = one_word(str, &i);
			if (wrd)
			{
				add_chunks_back(&chunks, wrd, WORD);
				// free(wrd);
			}
		}
		if (isredirection(str[i]))
		{
			wrd = get_op(str, &i);
			if (wrd)
			{
				add_chunks_back(&chunks, wrd, WORD);
				// free(wrd);
			}
		}
		j++;
	}
	return (chunks);
}

int	main(void)
{
	char	*str;
	t_chunk	*args;

	while (1)
	{
		str = readline(">  ");
		add_history(str);
		if (!check_redirection(str))
		{
			free(str);
			continue ;
		}
		args = get_chunk(str);
		while (args)
		{
			printf("%c", args->type);
			args = args->next;
		}
		printf("\n");
		free_chunks(args);
	}
	return (0);
}
