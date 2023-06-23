/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:25:23 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/22 13:11:24 by otchekai         ###   ########.fr       */
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

# define MAX_SIZE 4000000

# define WORD		0
# define HEREDOC	1
# define APPEND		2
# define FILE_IN	3
# define FILE_OUT	4
# define PIPE		5

# define RED	"\x1b[1;31m"
# define CYAN	"\x1b[1;36m"
# define RESET	"\x1b[0m"

typedef struct minishell
{
	char			**splitted;
	char			**path;
	char			**vne;
	char			*pwd;
	char			*line;
	char			*new_key;
	char			*new_val;
	int				join_val;
	struct s_list	*push;
	struct s_env	*s_env;
}	t_hell;

typedef struct s_list
{
	char				*data;
	int					token;
	int					id;
	struct s_list		*next;
	struct minishell	*minihell;
}	t_list;

typedef struct s_env
{
	char				*env_name;
	char				*env_value;
	struct s_env		*next;
	struct minishell	*minishell;
}	t_env;

		/*		Colors		*/
void	red(void);
void	green(void);
void	reset(void);
void	ft_errors(char *str);

		/*		Entry Point	*/
void	minihell_entrance(t_hell *mini);

		/*		Tools		*/
int		check_for_redirections(t_hell *mini, int i);
char	*ft_strcpy(char *dest, char *src);
int		remove_whitespaces_from_history(t_hell *mini);

		/*		Tools 2		*/
char	*add_whitespaces(t_hell *mini);
void	split_and_store(char *line, t_list *mini);

		/*		Misc		*/
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *data, int id, int token);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back1(t_env **lst, t_env *new);
t_env	*ft_lstnew1(char *env_name, char *env_value);
int		ft_lstsize1(t_env *lst);

		/* 		Syntax 		*/
int		all_begining_syntaxes(t_hell *mini);
int		all_middle_syntaxes(t_hell *mini);
int		all_ending_syntaxes(t_hell *mini);

int		append_begining(t_hell *mini);
int		append_middle(t_hell *mini);
int		append_ending(t_hell *mini);

int		heredoc_begining(t_hell *mini);
int		heredoc_middle(t_hell *mini);
int		heredoc_ending(t_hell *mini);

int		pipe_begining(t_hell *mini);
int		pipe_middle(t_hell *mini);
int		pipe_ending(t_hell *mini);

int		file_in_begining(t_hell *mini);
int		file_in_middle(t_hell *mini);
int		file_in_ending(t_hell *mini);

int		file_out_middle(t_hell *mini);
int		file_out_begining(t_hell *mini);
int		file_out_ending(t_hell *mini);

int		quotes(t_hell *mini);

		/* 		Envs 	*/
void	copy_env(t_env **lst, char **envs);

		/*		execution		*/
t_env	*check_env(t_env *lst, char *str);
void	print_current_directory(t_hell *mini);
int		export_first(t_hell *mini, char *str);
void	execution(t_hell *mini);
void	ft_export(t_env *lst, t_hell *mini);
void	print_env(t_hell *mini, t_env *tmp);
void	update_pwds(t_env *lst, t_hell *mini);
void	change_directory(t_hell *mini, t_env *lst);
void	unset(t_env **lst, t_hell *mini);
void	echo(t_hell *mini);
int		check_n(char *str);

#endif