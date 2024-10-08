/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:32:07 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/08 09:22:23 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <libft.h>
# include <lexer.h>
# include <error.h>
# include <parser.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

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

int		handle_eof(char *str);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	free_chunks(t_chunk *lst);
void	ms_pwd(char *str);
void	ms_cd(char *str);
char	*get_variable(char *str);
char	*expander(char *str, char **envp);
int		str_isnum(char *str);
int		table_isnum(char **str);
void	ms_echo(t_chunk *chunks, char **env);
void	ms_env(char *str, char **env);
void	ms_builtins(t_chunk *chunks, char *str, char **env);
void	ms_export(char **env, t_chunk *chunks);

#endif
