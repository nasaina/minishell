/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:48:44 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/22 14:56:14 by nandrian         ###   ########.fr       */
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

int			name_token(char *str, int *i, char **name);
int			ignore_value(char	*str, char **result, int *i, int *status);
int			insert_char(char **result, char *str, int *status, int *i);
int			dquote_status(char *str);
int			no_quote(char *str, int i);
int			quote_simple(char *str, int i);
int			quote_double(char *str, int i);
int			char_isquote(char c);
int			name_token(char *str, int *i, char **name);
int			handle_exit(t_expander *expander, t_env *env);
char		*get_command(char *str);
char		*str_insert(char *str, int count, int *i);
char		*join_char(char *str, char c);
char		*get_value(char *str);
char		*ms_getenv(char *str, t_env *env);
char		*get_var_name(char *str, int i);
char		*join_char(char *str, char c);
char		*get_var_name(char *str, int i);
char		*handle_dquote(char *str, int *i);
char		*handle_squote(char *str, int *i);
void		env_value(char **result, int *i, t_env *env, char *name);
void		add_expanders_back(t_expander **args, char *str, t_type type);
void		free_expander(t_expander *expander);
t_expander	*expand_str(t_chunk *chunks, t_env *env);
int			split_token(char **result, t_chunk **token, int *status, char **split);
int			extract_double(char *str, char **result, int *i);
int			extract_word(char *str, char **result, int *i, int status);
int			extract_single(char *str, char **result, int *i);
char		*extract_noquote(char *str, int *status, int *i);
void		ignore_special(char *str, char **result, int *i);
void		extract_qvalue(char *str, char **result, int *i, t_env *env);
void		ignore_single(char *str, int *i, char **result);
void		ignore_special(char *str, char **result, int *i);
char		**ignore_split(char *str, int *i, int *status, t_chunk **token);
int			ignore_double(char *str, int *i);
int			ignore_digit(char *str, int *i);
int			extract_status(char **result, int *i, char *str);
int			check_split(char **str);
void		extract_qvalue(char *str, char **result, int *i, t_env *env);
int			extract_value(char *str, int *i, char **result, int status);
int			is_nword(char *str);
int			token_nword(char *str, t_chunk **token, t_type type);
void		assemble_token(char *str, char *result, t_chunk **token, int i);
char		**add_split(char *str, int	*status, int *i, t_chunk **token);
int			split_all(t_chunk **token, char **result, int *status, char **split);
void		init_token(t_chunk **token, t_env *env, int *i, char **result);

#endif