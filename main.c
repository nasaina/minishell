/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:38:26 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/14 17:12:19 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signal.h>

char *get_op(char *str, int *i)
{
	char	*wrd;


	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		str = readline(">  ");
		if (handle_eof(str))
			break ;
		split = ft_split(str, ' ');
		check_redirection(str);
		add_history(str);
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
	int		count;

	count = 0;
	while (str[*i] == 32)
		*i += 1;
	while (isredirection(str[*i]))
		*i += 1;	
	while (str[*i] && !isredirection(str[*i]) && str[*i] != 32)
	{
		count++;
		*i += 1;
	}
	if (!str[*i])
		return (NULL);
	wrd = malloc(count + 1);
	j = 0;
	while (j < count)
	{
		wrd[j] = str[*i];
		j++;
		*i += 1;
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

t_lexer *get_lexer(t_lexer *args, char *str)
{
	char	*wrd;
	int		count;
	t_type	type;
	int		i;
	int		j;

	i = 0;
	j = 0;
	count = count_word(str);
	while (i < count)
	{
		if (str[j] != '\0')
		{
			if (str[j] == 32)
				j++;
			else if (str[j] != 32 && !isredirection(str[j]) && str[j])
			{
				wrd = one_word(str, &j);
				type = WORD;
			}
			else if (str[j] == '>')
			{
				j++;
				wrd = malloc(2);
				wrd[0] = '>';
				wrd[1] = '\0';
				type = OUT;
			}
			else if (str[j] == '<')
			{
				j++;
				wrd = malloc(2);
				wrd[0] = '<';
				wrd[1] = '\0';
				type = IN;
			}
			else if (str[j] == '>' && str[j + 1] == '>')
			{
				j += 2;
				wrd = malloc(3);
				wrd[0] = '>';
				wrd[1] = '>';
				wrd[2] = '\0';
				type = APPEND;
			}
			else if (str[j] == '<' && str[j + 1] == '<')
			{
				j += 2;
				wrd = malloc(3);
				wrd[0] = '<';
				wrd[1] = '<';
				wrd[2] = '\0';
				type = HEREDOC;
			}
		}
		else
			return (NULL);
		int len = ft_strlen(wrd);
		for (int f = 0; f < len; f++)
		{
			add_back(&args, wrd[f]);
		}
		i++;
	}
	return (args);
}

// int	main(void)
// {
// 	char	*str;
// 	t_lexer	*args;

// 	args = NULL;
// 	while (1)
// 	{
// 		str = readline(">  ");
// 		add_history(str);
// 		if (!check_redirection(str))
// 		{
// 			free(str);
// 			continue ;
// 		}
// 		args = get_lexer(args, str);
// 		while (args)
// 		{
// 			printf("%c\n", args->c);
// 			args = args->next;
// 		}
// 		// printf("\n");
// 		free_lst(args);
// 	}
// 	return (0);
// }

int	get_len(char *str, int i)
{
	while (str[i] != 32 && !isredirection(str[i]))
		i++;
	return (i);
}


int	main(int ac, char **av)
{
	char 	*wrd;
	t_chunk	*args = NULL;
	int		i = 0;
	int		j = 0;
	int		count = 0;
	char	*str = av[1];
	
	(void)ac;
	while (str[i])
	{
		if (str[i] == '>')
		{
			printf("OUT %c\n", str[i]);
			wrd = malloc(2);
			wrd[0] = str[i];
			wrd[1] = '\0';
			add_chunks_back(&args, wrd, OUT);
		}
		else if (str[i] == '<')
		{
			printf("IN %c\n", str[i]);
			wrd = malloc(2);
			wrd[0] = str[i];
			wrd[1] = '\0';
			add_chunks_back(&args, wrd, IN);
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			printf("APP %c\n", str[i]);
			wrd = malloc(3);
			wrd[0] = str[i];
			wrd[1] = str[i + 1];
			wrd[2] = '\0';
			add_chunks_back(&args, wrd, APPEND);
		}
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			printf("HERE %c\n", str[i]);
			wrd = malloc(3);
			wrd[0] = str[i];
			wrd[1] = str[i + 1];
			wrd[2] = '\0';
			add_chunks_back(&args, wrd, HEREDOC);
		}
		else if (str[i] == 32)
			i++;
		else if (str[i] != '\0')
		{
			count = get_len(str, i);
			wrd = malloc(count + 1);
			while (str[i] != 32 && !isredirection(str[i]) && str[i])
			{
				wrd[j] = str[i];
				i++;
				j++;
				printf("%c ", str[i]);
			}
			wrd[j] = '\0';
			add_chunks_back(&args, wrd, WORD);
		}
		i++;
	}
	wrd = NULL;
	free(wrd);	
	// while (args->next)
	// {
	// 	printf("%u %s \n", args->type, args->str);
	// 	args = args->next;
	// }
	free_chunks(args);
}