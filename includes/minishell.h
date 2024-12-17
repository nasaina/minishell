/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:32:07 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/17 13:11:23 by maandria         ###   ########.fr       */
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
int		handle_eof(char *str, t_export *export);
int		isbuiltin(t_ast *ast);
int		exec_cmd(t_ast *ast, char **env);
int		check_cmd(t_ast *ast, t_export *export, char **env);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	free_chunks(t_chunk *lst);
int		ms_pwd(t_ast *ast);
int		ms_cd(t_ast *ast, t_export *export);
int		exec_pipe(t_ast *ast, t_export *export, char **env);
int		pipe_check(t_ast *ast, t_export *export, char **env);
int		str_isnum(char *str);
int		table_isnum(char **str);
void	ms_echo(t_cmd *cmd);
void	ms_env(char **str, t_export *export);
void	ms_unset(t_export **export, char **str);
int		ms_builtins(t_ast *ast, t_export *export);
void	ms_export(char **env, t_chunk *chunks);
void	exec_pipe_left(t_ast *ast, t_export *export,
			char **env, int *pipe_fds);
int		exec_pipe_right(t_ast *ast, t_export *export,
			char **env, int *pipe_fds);
char 	*var_remove(char *str);
void	do_redir(t_ast *ast);
void	remove_env(t_export **export, char *str);
void	free_ast(t_ast *ast);
void		get_input(t_redir *heredoc, t_export *export, char *file);
int		heredoc_check(t_chunk *chunks);
t_redir	*expand_hdoc(char *str);
t_export	*ms_envcpy(char **env);
void		sort_env(t_export **export);
void		ft_printenv(t_export *export, int *i);
void		print_export(t_export *export);
void		is_double(t_export **export, char *name);
int			check_input(char **args, int i, char *name);
int			double_input(char **str, int i, char *args);
int			is_invalidname(char *str);
char		*export_name(char *str);
int			hdoc_oneword(char *str, int i, t_type *type);
int			hdoc_count(int count, char *str, int i, t_type *type);
t_chunk		*hdoc_token(char *str);
int			is_variable(char *str);
int			heredoc_check(t_chunk *chunks);
t_redir		*expand_hdoc(char *str);
char		*join_free(char *s1, char *s2);

#endif
