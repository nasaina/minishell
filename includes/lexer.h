/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:02:10 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/10 15:51:13 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_type
{
	WORD = 0,
	OUT = 1,
	IN = 2,
	APPEND = 3,
	HEREDOC = 4,
	PIPE = 5,
}	t_type;

typedef struct s_chunk
{
	t_type			type;
	char			*str;
	struct s_chunk	*next;
}	t_chunk;

int		one_word(char *str, int i, t_type *type);
int		is_append(char *str, int i, t_type *type);
int		is_heredoc(char *str, int i, t_type *type);
int		is_word(char c);
int 	qword_len(char *str, int i);
int		is_quote(char *str, int i, t_type *type);
int		is_variable(char *str);
void	add_chunks_back(t_chunk **args, char *str, t_type type);
void	add_chunks_front(t_chunk **args, char *str, t_type type);
t_chunk	*lexing(char *str);
int	count_args(int count, char *str, int i, t_type *type);

#endif
