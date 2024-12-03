/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:32:07 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/03 16:34:17 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <includes.h>

# define NC		"\e[0m"
# define YELLOW	"\e[1;33m"
# define RED	"\e[31m"
# define GREEN	"\e[1;32m"
# define CYAN	"\e[1;36m"

typedef struct s_lexer
{
	char			c;
	struct s_lexer	*next;
}	t_lexer;

const char	**init_builtins(void);
int		handle_eof(char *str);
int		isbuiltin(t_ast *ast);
void	exec_cmd(t_ast *ast, char **env);
void	check_cmd(t_ast *ast, t_export *export, char **env);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	free_chunks(t_chunk *lst);
void	ms_pwd(t_ast *ast);
void	ms_cd(t_ast *ast);
void	exec_pipe(t_ast *ast, t_export *export, t_expander *expander, char *str, char **env);
void	pipe_check(t_ast *ast, t_export *export, t_expander *expander, char *str, char **env);
void	pipe_fd(t_ast *ast, t_export *export, t_expander *expander, char *str, char **env);
int		str_isnum(char *str);
int		table_isnum(char **str);
void	ms_echo(t_cmd *cmd);
void	ms_env(char **str, t_export *export);
void	ms_unset(t_export **export, char **str);
void	ms_builtins(t_ast *ast, t_export *export);
void	ms_export(char **env, t_chunk *chunks);
char 	*var_remove(char *str);
void	do_redir(t_cmd *cmd);

#endif
