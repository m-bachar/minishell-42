# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 22:20:05 by mbachar           #+#    #+#              #
#    Updated: 2023/08/06 17:25:04 by mbachar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL 	= 	minishell

CFLAGS 		=	-Wall -Werror -Wextra -g -fsanitize=address

INC 		= 	minishell.h

CC			=	cc

LIBFT		=	./libft/libft.a

MAN_SRC 	=	minishell.c \
				./src/misc/errors.c \
				./src/misc/lst.c \
				./src/misc/lst2.c \
				./src/misc/tools.c \
				./src/misc/tools2.c \
				./src/misc/tools3.c \
				./src/misc/split2.c \
				./src/minihell_entrance.c \
				./src/split_and_store.c \
				./src/norminette.c \
				./src/syntax/append.c \
				./src/syntax/heredoc.c \
				./src/syntax/file_in.c \
				./src/syntax/file_out.c \
				./src/syntax/pipe.c \
				./src/syntax/all_in_one.c \
				./src/syntax/quotes.c \
				./src/parsing/env.c \
				./src/parsing/append.c \
				./src/parsing/heredoc.c \
				./src/parsing/file_in.c \
				./src/parsing/file_out.c \
				./src/parsing/expand.c \
				./src/parsing/expand_in_heredoc.c \
				./src/redirections_leaks.c \
				./src/builtins/export.c \
				./src/builtins/pwd.c \
				./src/builtins/cd.c \
				./src/builtins/unset.c \
				./src/builtins/echo.c \
				./src/builtins/exit.c \
				./src/execution/execve.c \
				./src/execution/signals.c

MAN_OBJ		=	$(MAN_SRC:.c=.o)

all: $(MINISHELL)

%.o : %.c $(INC)
	@ $(CC) $(CFLAGS) -c $< -o $@ -I$(shell brew --prefix readline)/include

$(MINISHELL): $(MAN_OBJ)
	@ cd ./libft && make
	@ $(CC) $(CFLAGS) $(MAN_OBJ) -o $(MINISHELL) $(LIBFT) -L$(shell brew --prefix readline)/lib -lreadline
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
