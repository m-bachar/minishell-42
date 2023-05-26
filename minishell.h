/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:25:23 by mbachar           #+#    #+#             */
/*   Updated: 2023/05/26 08:18:05 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "./libft/libft.h"

# define MAX_SIZE 100000

# define WORD		(0)
# define HEREDOC	(1)
# define APPEND		(2)
# define FILE_IN	(3)
# define FILE_OUT	(4)
# define PIPE		(5)

# define RED	"\x1b[1;31m"
# define CYAN	"\x1b[1;36m"
# define RESET	"\x1b[0m"

typedef struct minishell
{
	char			*line;
	struct s_list	*push;
}	t_hell;

typedef struct s_list
{
	char				*data;
	int					token;
	int					id;
	struct s_list		*next;
	struct minishell	*minihell;
}	t_list;

/*	./src/misc/errors.c	*/
void	red(void);
void	green(void);
void	reset(void);
void	ft_errors(char *str);

/*	./src/syntax.c	*/ // TBU
void	minihell_entrance(t_hell *mini);

/*	./src/misc/tools.c	*/
int		check_for_redirections(t_hell *mini, int i);
char	*ft_strcpy(char *dest, char *src);
int		remove_whitespaces_from_history(t_hell *mini);

/*	./src/split_and_store.c	*/
char	*add_whitespaces(t_hell *mini);
void	split_and_store(char *line, t_list *mini);

/*	./src/misc/lst.c	*/
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *data, int id, int token);
int		ft_lstsize(t_list *lst);

/*	./src/syntax/all_in_one.c	*/
int		all_begining_syntaxes(t_hell *mini);
int		all_middle_syntaxes(t_hell *mini);
int		all_ending_syntaxes(t_hell *mini);

/*	./src/syntax/append.c	*/
int		append_begining(t_hell *mini);
int		append_middle(t_hell *mini);
int		append_ending(t_hell *mini);

/*	./src/syntax/heredoc.c	*/
int		heredoc_begining(t_hell *mini);
int		heredoc_middle(t_hell *mini);
int		heredoc_ending(t_hell *mini);

/*	./src/syntax/pipe.c	*/
int		pipe_begining(t_hell *mini);
int		pipe_middle(t_hell *mini);
int		pipe_ending(t_hell *mini);

/*	./src/syntax/file_in.c	*/
int		file_in_begining(t_hell *mini);
int		file_in_middle(t_hell *mini);
int		file_in_ending(t_hell *mini);

/*	./src/syntax/file_out.c	*/
int		file_out_middle(t_hell *mini);
int		file_out_begining(t_hell *mini);
int		file_out_ending(t_hell *mini);

/*	./src/syntax/quotes.c	*/
int		quotes(t_hell *mini);

#endif