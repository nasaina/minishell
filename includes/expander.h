/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:48:44 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/13 11:44:25 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <lexer.h>
# include <exec.h>

typedef struct s_expander
{
	t_type				type;
	char				*cmd;
	struct s_expander	*next;	
}	t_expander;

t_expander	*expand_str(t_chunk *chunks, t_export *export);
char		*get_name(char *str);
char		*get_value(char *str);
char		*ms_getenv(char *str, t_export *export);
void		add_expanders_back(t_expander **args, char *str, t_type type);
void		free_expander(t_expander *expander);
char		*expander(char *str, t_export *export);
t_chunk		*expanded(char *str, t_type type, t_export *export);
char		*get_var_name(char *str, int i);
char		*join_char(char *str, char c);
int			name_token(char *str, int *i, char **name);
char		*export_value(char **result, int *i, t_export *export, char *name);
char		*get_var_name(char *str, int i);
int			no_quote(char *str, int i);
int			quote_simple(char *str, int i);
int			quote_double(char *str, int i);
int			char_isquote(char c);
int			name_token(char *str, int *i, char **name);
char		*handle_dquote(char *str, int *i);
char		*handle_squote(char *str, int *i);
int			dquote_status(char *str);
char		*get_command(char *str);
char		*str_insert(char *str, int count, int *i);
char		*join_char(char *str, char c);
int			ignore_value(char	*str, char **result, int *i, int *status);

#endif