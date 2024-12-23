NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

OBJ_DIR = objs

INCLUDES = -I includes/

INC_LIBFT = -I libft/

LIBFT = libft/libft.a

SRC_SIG = $(addprefix src/signals/, handle_signals.c)

SRC_HD = $(addprefix src/executor/heredoc/, build_heredoc.c count_heredoc.c expand_heredoc.c handle_heredoc.c value_heredoc.c)

SRC_TOKEN = $(addprefix src/expander/expand_token/, token_value.c split_token.c ignore_value.c extract_value.c check_token.c token_count.c init_token.c)

SRC_EXP = $(addprefix src/expander/, expander.c get_var.c create_expander.c str_duplicate.c handle_quote.c)

SRC_PARS = $(addprefix src/parser/, parser.c create_redir.c)

SRC_ERR = $(addprefix src/errors/, error.c args_utils.c)

SRC_EXPORT = $(addprefix src/builtins/ms_export/, check_export.c ms_export.c print_env.c)

SRC_BUILT = $(addprefix src/builtins/, builtins.c create_t_env.c handle_exit.c ms_cd.c ms_echo.c ms_pwd.c ms_unset.c)

SRC_EXEC = $(addprefix src/executor/, execute.c path_checker.c exec_pipe.c redir.c path_access.c exit_status.c execute_utils.c exec_redir.c)

SRC_LEX = $(addprefix src/lexer/, lexer.c get_chunks.c check_op.c quote.c)

SRC_UTILS = $(addprefix src/utils/, free_lst.c str_isnum.c ft_strcmp.c join_and_free.c handle_history.c)

SRC_GNL = $(addprefix src/gnl/, gnl.c gnl_utils.c)

MAIN = main.c

OBJ_SIG = $(SRC_SIG:%.c=$(OBJ_DIR)/%.o)

OBJ_HD = $(SRC_HD:%.c=$(OBJ_DIR)/%.o)

OBJ_BUILT = $(SRC_BUILT:%.c=$(OBJ_DIR)/%.o)

OBJ_EXP = $(SRC_EXP:%.c=$(OBJ_DIR)/%.o)

OBJ_PARS = $(SRC_PARS:%.c=$(OBJ_DIR)/%.o)

OBJ_ERR = $(SRC_ERR:%.c=$(OBJ_DIR)/%.o)

OBJ_EXEC = $(SRC_EXEC:%.c=$(OBJ_DIR)/%.o)

OBJ_LEX = $(SRC_LEX:%.c=$(OBJ_DIR)/%.o)

OBJ_UTILS = $(SRC_UTILS:%.c=$(OBJ_DIR)/%.o)

OBJ_GNL = $(SRC_GNL:%.c=$(OBJ_DIR)/%.o)

OBJ_EXPORT = $(SRC_EXPORT:%.c=$(OBJ_DIR)/%.o)

OBJ_MAIN = $(MAIN:%.c=$(OBJ_DIR)/%.o)

OBJ_TOKEN = $(SRC_TOKEN:%.c=$(OBJ_DIR)/%.o)

OBJS = $(OBJ_EXEC) $(OBJ_PARS) $(OBJ_UTILS) $(OBJ_LEX) $(OBJ_EXPORT) $(OBJ_ERR) $(OBJ_BUILT) $(OBJ_SIG) $(OBJ_EXP) $(OBJ_TOKEN) $(OBJ_HD) $(OBJ_GNL) $(OBJ_MAIN)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME) $(INCLUDES) $(INC_LIBFT)
	@clear
	@echo "\n\e[1;91mExecute the program with \e[0m./minishell\n"

$(OBJ_DIR)/%.o : %.c
	@make -C libft
	@mkdir -p '$(@D)'
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC_LIBFT) $(INCLUDES)

clean :
	@make fclean -C libft
	@rm -rf $(OBJ_DIR)
	@clear
	@echo "\n\e[1;32mLibrary successfuly deleted\e[0m\n"

fclean : clean
	@rm -rf $(NAME)
	@clear
	@echo "\n\e[1;32mLibrary successfuly deleted\e[0m\n"

re : fclean all

v:
	valgrind --suppressions=readline.supp  --leak-check=full --track-fds=yes --show-leak-kinds=all ./minishell

.PHONY : all clean fclean re
