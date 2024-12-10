/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:32:07 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/10 15:53:59 by nandrian         ###   ########.fr       */
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

typedef struct s_heredoc
{
	int					status;
	char				*str;
	struct s_heredoc	*next;
}	t_heredoc;


char	**init_builtins(void);
char	*check_path(char **pathlist, t_ast *ast);
char	*check_access(t_ast *ast);
int		handle_eof(char *str);
int		isbuiltin(t_ast *ast);
void	exec_cmd(t_ast *ast, char **env);
void	check_cmd(t_ast *ast, t_export *export, char **env);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	free_chunks(t_chunk *lst);
void	ms_pwd(t_ast *ast);
void	ms_cd(t_ast *ast);
void	exec_pipe(t_ast *ast, t_export *export, char **env);
void	pipe_check(t_ast *ast, t_export *export, char **env);
int		str_isnum(char *str);
int		table_isnum(char **str);
void	ms_echo(t_cmd *cmd);
void	ms_env(char **str, t_export *export);
void	ms_unset(t_export **export, char **str);
void	ms_builtins(t_ast *ast, t_export *export);
void	ms_export(char **env, t_chunk *chunks);
void	exec_pipe_left(t_ast *ast, t_export *export, char **env, int *pipe_fds);
void	exec_pipe_right(t_ast *ast, t_export *export, char **env, int *pipe_fds);
char 	*var_remove(char *str);
void	do_redir(t_cmd *cmd);
void	remove_env(t_export **export, char *str);
void	free_ast(t_ast *ast);
int		get_input(t_redir *heredoc, t_export *export);
int		heredoc_check(t_chunk *chunks);
t_redir	*expand_hdoc(char *str);

#endif
