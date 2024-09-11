NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

OBJ_DIR = objs

INCLUDES = -I includes/

INC_LIBFT = -I libft/

LIBFT = libft/libft.a

SRC_PARS = $(addprefix src/parser/, is_space.c)

SRC_EXEC = $(addprefix src/executor/, execute.c)

SRC_LEX = $(addprefix src/lexer/, lexer.c)

MAIN = main.c

OBJ_PARS = $(SRC_PARS:%.c=$(OBJ_DIR)/%.o)

OBJ_EXEC = $(SRC_EXEC:%.c=$(OBJ_DIR)/%.o)

OBJ_LEX = $(SRC_LEX:%.c=$(OBJ_DIR)/%.o)

OBJ_MAIN = $(MAIN:%.c=$(OBJ_DIR)/%.o)

OBJS = $(OBJ_EXEC) $(OBJ_PARS) $(OBJ_LEX) $(OBJ_MAIN)

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