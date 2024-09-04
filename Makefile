NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

OBJ_DIR = objs

INCLUDES = -I includes/

INC_LIBFT = -I libft/

LIBFT = libft/libft.a

SRC_PARSING = $(addprefix src/parsing/, is_space.c lexer.c)

SRC_EXEC = $(addprefix src/executing/, execute.c)

MAIN = main.c

OBJ_PARSING = $(SRC_PARSING:%.c=$(OBJ_DIR)/%.o)

OBJ_EXEC = $(SRC_EXEC:%.c=$(OBJ_DIR)/%.o)

OBJ_MAIN = $(MAIN:%.c=$(OBJ_DIR)/%.o)

OBJS = $(OBJ_EXEC) $(OBJ_PARSING) $(OBJ_MAIN)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(INCLUDES) $(INC_LIBFT)
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