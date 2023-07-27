# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 22:20:05 by mbachar           #+#    #+#              #
#    Updated: 2023/07/27 02:33:50 by mbachar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL 	= 	minishell

CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address

LDFLAGS		=	"-L/goinfre/mbachar/homebrew/opt/readline/lib"

CPPFLAGS	=	"-I/goinfre/mbachar/homebrew/opt/readline/include" -lreadline

INC 		= 	minishell.h

CC			=	cc

LIBFT		=	./libft/libft.a

MAN_SRC 	=	minishell.c \
				./src/misc/errors.c \
				./src/misc/tools.c \
				./src/misc/tools2.c \
				./src/syntax.c \
				./src/split_and_store.c \
				./src/norminette.c \
				./src/misc/lst.c \
				./src/misc/lst2.c \
				./src/syntax/append.c \
				./src/syntax/heredoc.c \
				./src/syntax/file_in.c \
				./src/syntax/file_out.c \
				./src/syntax/pipe.c \
				./src/syntax/all_in_one.c \
				./src/syntax/quotes.c \
				./src/parsing/parsing.c \
				./src/parsing/append.c \
				./src/parsing/heredoc.c \
				./src/parsing/file_in.c \
				./src/parsing/file_out.c \
				./src/parsing/expand.c \
				./src/builtins/export.c \
				./src/builtins/pwd.c \
				./src/builtins/cd.c \
				./src/builtins/unset.c \
				./src/builtins/echo.c \
				./src/builtins/exit.c \
				./src/execution/execve.c

MAN_OBJ		=	$(MAN_SRC:.c=.o)

all: $(MINISHELL)

%.o : %.c $(INC)
	@ $(CC) $(CFLAGS) -c $< -o $@

$(MINISHELL): $(MAN_OBJ)
	@ cd ./libft && make
	@ $(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) $(MAN_OBJ) -o $(MINISHELL) $(LIBFT)
	@ printf "==================================================\n"
	@ printf "All mandatory source files have been compiled.\n"
	@ printf "Executable file minishell has been generated.\n"
	@ printf "==================================================\n"

clean:
	@ rm -fr $(MAN_OBJ)
	@ cd ./libft && make clean
	@ printf "==================================================\n"
	@ printf "All object files have been destroyed.\n"
	@ printf "==================================================\n"

fclean:
	@ rm -fr $(MINISHELL) $(MAN_OBJ)
	@ cd ./libft && make fclean
	@ printf "=============================================================\n"
	@ printf "All object files and executable file have been destroyed.\n"
	@ printf "=============================================================\n"

re: fclean all

.PHONY: fclean clean re