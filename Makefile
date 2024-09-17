NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

OBJ_DIR = objs

INCLUDES = -I includes/

INC_LIBFT = -I libft/

LIBFT = libft/libft.a

SRC_SIG = $(addprefix src/signals/, handle_signals.c)

SRC_EXP = $(addprefix src/expander/, expander.c)

SRC_PARS = $(addprefix src/parser/, is_space.c)

SRC_ERR = $(addprefix src/errors/, error.c args_utils.c)

SRC_EXEC = $(addprefix src/executor/, execute.c)

SRC_LEX = $(addprefix src/lexer/, lexer.c get_chunks.c check_op.c)

SRC_UTILS = $(addprefix src/utils/, lst_utils.c free_lst.c)

MAIN = main.c

OBJ_SIG = $(SRC_SIG:%.c=$(OBJ_DIR)/%.o)

OBJ_EXP = $(SRC_EXP:%.c=$(OBJ_DIR)/%.o)

OBJ_PARS = $(SRC_PARS:%.c=$(OBJ_DIR)/%.o)

OBJ_ERR = $(SRC_ERR:%.c=$(OBJ_DIR)/%.o)

OBJ_EXEC = $(SRC_EXEC:%.c=$(OBJ_DIR)/%.o)

OBJ_LEX = $(SRC_LEX:%.c=$(OBJ_DIR)/%.o)

OBJ_UTILS = $(SRC_UTILS:%.c=$(OBJ_DIR)/%.o)

OBJ_MAIN = $(MAIN:%.c=$(OBJ_DIR)/%.o)

OBJS = $(OBJ_EXEC) $(OBJ_PARS) $(OBJ_UTILS) $(OBJ_LEX) $(OBJ_ERR) $(OBJ_SIG) $(OBJ_EXP) $(OBJ_MAIN)

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
