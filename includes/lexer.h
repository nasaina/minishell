/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:02:10 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/16 13:06:16 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_type
{
	WORD,
	OUT,	
	IN,	
	APPEND,	
	HEREDOC,
	PIPE,
	NONE
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
int		is_variable(char *str);
void	add_chunks_back(t_chunk **args, char *str, t_type type);
void	add_chunks_front(t_chunk **args, char *str, t_type type);
t_chunk	*lexing(t_chunk *chunks, char *str);

#endif