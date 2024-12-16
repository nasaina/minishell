NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

OBJ_DIR = objs

INCLUDES = -I includes/

INC_LIBFT = -I libft/

LIBFT = libft/libft.a

SRC_SIG = $(addprefix src/signals/, handle_signals.c)

SRC_EXP = $(addprefix src/expander/, expander.c get_var.c create_expander.c token_count.c str_duplicate.c handle_quote.c)

SRC_PARS = $(addprefix src/parser/, parser.c create_redir.c)

SRC_ERR = $(addprefix src/errors/, error.c args_utils.c err_quote.c)

SRC_BUILT = $(addprefix src/builtins/, directory.c builtins.c export.c create_t_export.c export_env.c unset.c utils_echo.c init_builtins.c print_export.c handle_exit.c)

SRC_EXEC = $(addprefix src/executor/, execute.c path_checker.c exec_pipe.c redir.c handle_heredoc.c path_access.c expand_heredoc.c)

SRC_LEX = $(addprefix src/lexer/, lexer.c get_chunks.c check_op.c quote.c)

SRC_UTILS = $(addprefix src/utils/, free_lst.c str_isnum.c export_utils.c join_and_free.c handle_history.c)

SRC_GNL = $(addprefix src/get_next_line/, get_next_line.c get_next_line_utils.c)

MAIN = main.c

OBJ_SIG = $(SRC_SIG:%.c=$(OBJ_DIR)/%.o)

OBJ_BUILT = $(SRC_BUILT:%.c=$(OBJ_DIR)/%.o)

OBJ_EXP = $(SRC_EXP:%.c=$(OBJ_DIR)/%.o)

OBJ_PARS = $(SRC_PARS:%.c=$(OBJ_DIR)/%.o)

OBJ_ERR = $(SRC_ERR:%.c=$(OBJ_DIR)/%.o)

OBJ_EXEC = $(SRC_EXEC:%.c=$(OBJ_DIR)/%.o)

OBJ_LEX = $(SRC_LEX:%.c=$(OBJ_DIR)/%.o)

OBJ_UTILS = $(SRC_UTILS:%.c=$(OBJ_DIR)/%.o)

OBJ_GNL = $(SRC_GNL:%.c=$(OBJ_DIR)/%.o)

OBJ_MAIN = $(MAIN:%.c=$(OBJ_DIR)/%.o)

OBJS = $(OBJ_EXEC) $(OBJ_PARS) $(OBJ_UTILS) $(OBJ_LEX) $(OBJ_ERR) $(OBJ_BUILT) $(OBJ_SIG) $(OBJ_EXP) $(OBJ_GNL) $(OBJ_MAIN)

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

fclean : clean
	@rm -rf $(NAME)
	@clear

re : fclean all

.PHONY : all clean fclean re
