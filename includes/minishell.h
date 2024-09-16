/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:32:07 by nandrian          #+#    #+#             */

/*   Updated: 2024/09/14 15:37:03 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>

# define NC		"\e[0m"
# define YELLOW	"\e[1;33m"
# define RED	"\e[31m"
# define GREEN	"\e[1;32m"
# define CYAN	"\e[1;36m"

typedef struct s_lexer
{
	char 			c;
	struct s_lexer	*next;
}	t_lexer;

typedef enum e_type
{
	WORD,
	OUT,	
	IN,	
	APPEND,	
	HEREDOC,
	PIPE
}	t_type;

typedef struct s_chunk
{
	t_type			type;
	char 			*str;
	struct s_chunk	*next;
}	t_chunk;

void	add_back(t_lexer **args, char c);
void	add_front(t_lexer **args, char c);
int		check_redirection(char *str);
int		isredirection(char c);
int		is_redirok(char *str, int i);
int		is_redirok(char *str, int i);
t_lexer *get_args(t_lexer*args, char *str);
void	add_chunks_back(t_chunk **args, char *str, t_type type);
void	add_chunks_front(t_chunk **args, char *str, t_type type);
void	free_lst(t_lexer *lst);
void	free_chunks(t_chunk *lst);
char	*get_all_args(int ac, char **av);
char	**split_arg(char *args);
int		args_isalpha(char *str);
int		check_redirection(char *str);
int		handle_eof(char *str);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);

#endif
