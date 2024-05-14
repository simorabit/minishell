CC = cc
FLAGS = -Wall -Wextra -Werror
LIBS = -lreadline

SRC = main.c lexer_list.c parser.c utils_string.c ft_split.c \
	tokenizer.c utils_free.c quotes_spaces.c utils_quotes_spaces.c syntax_error.c \
	utils_split.c expanding.c
OBJ = $(SRC:.c=.o)

TARGET = minishell

all : $(TARGET)

$(TARGET) : $(OBJ) minishell.h
	$(CC) $(FLAGS) -o $@ $(OBJ) $(LIBS)

%.o : %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ) 

fclean : clean
	rm -rf $(TARGET)

re :	fclean all