CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
# -g -fsanitize=address
LIBS = -lreadline

SRC = main.c lexer_list.c utils_string.c ft_split.c \
	tokenizer.c utils_free.c quotes_spaces.c utils_quotes_spaces.c syntax_error.c \
	utils_split.c expanding/quotes_expanding.c libft_func.c or_split.c expanding/expanding.c expanding/utils.c \
	remove_quotes.c parser/parser.c parser/utils.c 

OBJ = $(SRC:.c=.o)

TARGET = minishell

all : $(TARGET)

$(TARGET) : $(OBJ) minishell.h
	@$(CC) $(FLAGS) -o $@ $(OBJ) $(LIBS)
	@echo "Compilation complete: $(TARGET) created successfully!"

%.o : %.c minishell.h
	@$(CC) $(FLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ)
	@echo "Object files removed successfully!"

fclean : clean
	@rm -rf $(TARGET)
	@echo "Executable '$(TARGET)' removed successfully!"

re : fclean all
