/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:38:37 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/26 16:10:17 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <lexer.h>

typedef enum s_vtape
{
	COMMAND,
	PIPE
}	t_vtype;

typedef struct s_cmd
{
	char	**args;
}	t_cmd;

typedef struct s_ast
{
	t_vtype			type;
	t_cmd			cmd;
	t_cmd			argument;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

int		count_cmd(t_chunk *chunks);
t_cmd	*get_cmd(t_chunk *chunks);

#endif