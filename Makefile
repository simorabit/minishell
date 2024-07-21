# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 12:34:57 by souaouri          #+#    #+#              #
#    Updated: 2024/07/21 16:02:50 by souaouri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 				=	cc
# -fsanitize=address -g
CC				+=	-Wall -Wextra -Werror 
NAME 			=	minishell
HEADER 			=	minishell.h

LIBS = -L $(shell brew --prefix readline)/lib -lreadline
LINKREADLINELIB1 = $(shell brew --prefix readline)/include

SRC = 	main.c parsing/lexer_list.c parsing/utils_string.c parsing/ft_split.c \
		parsing/tokenizer.c parsing/utils_free.c parsing/quotes_spaces.c parsing/utils_quotes_spaces.c \
		parsing/syntax_error.c parsing/utils_split.c parsing/expanding/quotes_expanding.c \
		parsing/libft_func.c parsing/expanding/expanding.c parsing/expanding/utils.c \
		parsing/utils.c parsing/remove_quotes.c parsing/parser/parser.c parsing/parser/utils_parser.c \
		parsing/parser/parser_files.c parsing/parser/cmds_op.c \
		execution/src/exec.c execution/builtins/cd.c execution/builtins/echo.c execution/builtins/pwd.c \
		execution/builtins/export_utile_1.c execution/builtins/export_utile_2.c execution/builtins/export_utile_3.c \
		execution/builtins/export_utile_4.c execution/builtins/env.c execution/builtins/env_utile.c execution/builtins/exit.c \
		execution/builtins/export.c execution/builtins/unset.c execution/utils/utils_1.c \
		execution/utils/utils_2.c execution/utils/utils_3.c execution/utils/utils_4.c \
		execution/utils/utils_5.c execution/utils/utils_6.c \
		execution/utils/utils_7.c execution/utils/utils_8.c debugging.c 

OBJ = $(SRC:.c=.o)

TARGET = minishell

all : $(TARGET)

$(TARGET) : $(OBJ) minishell.h
	@$(CC) $(FLAGS) -o $@ $(OBJ) $(LIBS)
	@echo "$(GREEN)[ + ] Compilation complete: $(TARGET) created successfully!$(RESET)"

%.o : %.c minishell.h
	@$(CC) $(FLAGS) -c -I $(LINKREADLINELIB1) $< -o $@

clean :
	@rm -rf $(OBJ)
	@echo "$(YELLOW)[ + ] Object files removed successfully!$(RESET)"

fclean : clean
	@rm -rf $(TARGET)
	@echo "$(YELLOW)[ + ] Executable '$(TARGET)' removed successfully!$(RESET)"

re : fclean all

RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
MAGENTA = \033[35m
CYAN    = \033[36m
RESET   = \033[0m

# CC 				=	cc -fsanitize=address -g
# CC				+=	-Wall -Wextra -Werror
# NAME 			=	minishell
# HEADER 			=	minishell.h
# DIR				=	.object_files

# SRC_FILES		=	exec.c
# BUILTS_FILES	=	cd.c			echo.c			pwd.c		\
# 					env.c			env_utile.c		export.c
# UTILS_FILES		=	utils_1.c 		utils_2.c 		utils_3.c 	\
# 					utils_4.c 		utils_5.c 		utils_6.c	\
# 					utils_7.c		utils_8.c
# VUR_FILES		=	list.c


# EXPAND_FILES	= 	expanding.c quotes_expanding.c utils.c 
# GET_NEXT_LINE 	= 	get_next_line.c get_next_line_utils.c 
# PARSER 			= 	cmds_op.c parser.c parser_files.c utils.c 
# OTHER_FILES 	= 	main.c lexer_list.c utils_string.c ft_split.c \
# 					tokenizer.c utils_free.c quotes_spaces.c utils_quotes_spaces.c \
# 					syntax_error.c utils_split.c


# EXPAND_SRC			=	$(addprefix parsing/expanding/,$(EXPAND_FILES))
# GET_NEXT_LINE_SRC	=	$(addprefix parsing/get_next_line/,$(GET_NEXT_LINE))
# PARSER_SRC			=	$(addprefix parsing/parser/,$(PARSER))
# OTHER_FILES_SRC		=	$(addprefix parsing/,$(OTHER_FILES))

# SRC_SRC			=	$(addprefix execution/src/,$(SRC_FILES))
# BUILTS_SRC		=	$(addprefix execution/builtins/,$(BUILTS_FILES))
# UTILS_SRC		=	$(addprefix execution/utils/,$(UTILS_FILES))
# VUR_SRC			=	$(addprefix execution/virtual/,$(VUR_FILES))


# EXPAND_OBJ			=	$(addprefix $(DIR)/,$(EXPAND_SRC:.c=.o))
# GET_NEXT_LINE_OBJ	=	$(addprefix $(DIR)/,$(GET_NEXT_LINE_SRC:.c=.o))
# PARSER_OBJ			=	$(addprefix $(DIR)/,$(PARSER_SRC:.c=.o))
# OTHER_FILES_OBJ		=	$(addprefix $(DIR)/,$(OTHER_FILES_SRC:.c=.o))

# SRC_OBJ			=	$(addprefix $(DIR)/,$(SRC_SRC:.c=.o))
# BUILTS_OBJ		=	$(addprefix $(DIR)/,$(BUILTS_SRC:.c=.o))
# UTILS_OBJ		=	$(addprefix $(DIR)/,$(UTILS_SRC:.c=.o))
# VUR_OBJ			=	$(addprefix $(DIR)/,$(VUR_SRC:.c=.o))

# OBJ_FILES		=	$(SRC_OBJ)	$(BUILTS_OBJ)	$(UTILS_OBJ)	\
# 					$(VUR_OBJ) $(parsing) $(GET_NEXT_LINE_OBJ) \
# 					$(PARSER_OBJ) $(OTHER_FILES_OBJ)

# all : $(NAME)

# $(NAME) : $(OBJ_FILES)
# 	@$(CC) -lreadline -o $@ $^
# 	@echo "✅ \033[1;32mCompilation Completed Successfully!\033[0;m"

# $(DIR)/src/%.o : src/%.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) -c $< -o $@
# 	@echo "\033[1;30mObject files generated Successfully! $@ \033[0;m"

# $(DIR)/builtins/%.o : builtins/%.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) -c $< -o $@
# 	@echo "\033[1;30mObject files generated Successfully! $@ \033[0;m"

# $(DIR)/utils/%.o : utils/%.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) -c $< -o $@
# 	@echo "\033[1;30mObject files generated Successfully! $@ \033[0;m"

# $(DIR)/virtual/%.o : virtual/%.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) -c $< -o $@
# 	@echo "\033[1;30mObject files generated Successfully! $@ \033[0;m"

# clean :
# 	@rm -rf $(DIR)
# 	@echo "\033[31mObject files has been removed Successfully! ✅\033[0;m"

# fclean : clean
# 	@rm -f $(NAME)
# 	@echo "\033[31mExecutable file has been removed Successfully! ✅\033[0;m"

# re : fclean all

# export > solimi | cat | cat | cat > solimi
# message error in parc and exec stop cmd to run becose infile=-1;
# message error "cmd not found"
# 5

#  //printf ("\n\n---> : %s\n\n", new);
# cat < Makefile > sssss
# dakchi nadii
# cat < Makefile | exit
# 77
# echo LLL | cat
# error !!: Invalid argument
# singl cmd builtins
#ls | ls | ls | cat < Makefile
#cat | cat | cat | ls -l
# get_content_from_eq_to_fin

# Tasks for soulaiman
# # 1- malloc
# 2- normitte
# 3- exit
# #  4- unset PATH | "env No such file or directory" add this
# # Tasks

# tasks for me
# addspaces
# signals cat minishell : minishell : 
# getenv
# cmd ; export ab="ls -l"

