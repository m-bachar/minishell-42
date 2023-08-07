/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otchekai <otchekai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:25:23 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/07 18:04:10 by otchekai         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include "./libft/libft.h"
# include <sys/ioctl.h>

# define MAX_SIZE 4000000

# define RED	"\x1b[1;31m"
# define CYAN	"\x1b[1;36m"
# define RESET	"\x1b[0m"

typedef struct minishell
{
	char			**path;
	char			**vne;
	char			*pwd;
	char			*var;
	char			*line;
	char			*to_find;
	char			*new_key;
	char			*new_val;
	int				join_val;
	int				i;
	int				j;
	int				expo_var;
	struct s_list	*push;
	struct s_env	*s_env;
}	t_hell;

typedef struct s_list
{
	char				*multi_cmds;
	char				**command;
	int					file_in;
	int					file_out;
	struct s_list		*next;
	struct minishell	*minihell;
}	t_list;

typedef struct s_env
{
	char				*env_name;
	char				*env_value;
	struct s_env		*next;
}	t_env;

		/*		Colors			*/
void	red(void);
void	green(void);
void	reset(void);
void	ft_errors(char *str);

		/*		Entry Point		*/
void	minihell_entrance(t_hell *mini);

		/*		Tools 1			*/
int		check_for_redirections(t_hell *mini, int i);
int		remove_whitespaces_from_history(t_hell *mini);
char	*add_whitespaces(t_hell *mini);
void	shape_shifting(char	*line);
void	nodes_shapeshifting(t_list **mini);

		/*		Tools 2			*/
char	*ft_strcpy(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
int		ft_strcmp2(char *s1, char *s2);
int		ft_strlen2(char *str);
void	free_mem(char **mem);

		/*		Tools 3			*/
int		isredirection(t_hell *mini, int i);
int		isredirection2(t_hell *mini, int i);
void	ft_clearmem(t_list **lst, t_hell **mini);
int		ft_strchr2(char *s, char c);
int		iswhitespace(char c);

		/*		Split 2			*/
char	**ft_split2(char *s, char *c);

		/*		Split & Store	*/
void	split_and_store(char *line, t_list **mini);
void	split_and_store2(t_list **list);

		/*		Lists 1			*/
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *data);
int		ft_lstsize(t_list *lst);

		/*		Lists 2			*/
void	ft_lstadd_back1(t_env **lst, t_env *new);
t_env	*ft_lstnew1(char *env_name, char *env_value);
int		ft_lstsize1(t_env *lst);

		/* 		Syntax 			*/
int		all_begining_syntaxes(t_hell *mini);
int		all_middle_syntaxes(t_hell *mini);
int		all_ending_syntaxes(t_hell *mini);
int		all_in_one(t_hell *mini);

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

		/*		Parsing				*/
int		open_and_heredoc(t_list **mini, t_env **env);
int		open_and_append(char *str1, char *str2, t_list *list);
int		open_and_output(char *str1, char *str2, t_list *list);
int		open_and_input(char *str1, char *str2, t_list *list);
char	*rand_name(void);
int		remove_NADA(t_list **mini);

		/*		Expand				*/
char	*extract_var_value(t_env **env, char *env_name);
void	extract_var_name(char *data, char **returned_var,
			t_hell *mini, t_env **env);
char	*expand_or_skip(char *str, t_hell *mini, t_env **env);
void	skip_or_replace(t_list	**mini, t_env **env, t_hell *hell);
void	single_quotes2(t_hell *mini, char *final_var, char *str);
void	double_quotes2(t_hell *mini, char *final_var, char *str, t_env **env);

		/*		Expand in Heredoc	*/
char	*extract_var_value_heredoc(t_env **env, char *env_name);
char	*extract_var_name_heredoc(char *data);
char	*expand_in_heredoc(char *line, t_env **env);

		/*		Builtins			*/
t_env	*check_env(t_env *lst, char *str);
int		export_first(t_hell *mini, char *str);
int		check_n(char *str);
void	copy_env(t_env **lst, char **envs);
void	print_current_directory(t_hell *mini);
void	ft_export(t_env **lst, t_hell *mini, t_list *list);
void	update_pwds(t_env *lst, t_list *list);
void	change_directory(t_list *list, t_env *lst);
void	unset(t_env **lst, t_list *list);
void	echo(t_list *list);
void	print_export(t_env *lst);
void	print_env(t_env *lst);
void	exit_hell(char **str);

		/*		Redirections Leaks		*/
void	remove_args_from_redirections(t_list **mini);
int		remove_nada(t_list **mini);

		/*      Execution        	*/
void	one_command(t_hell *mini, t_env **lst, t_list *split);
void	commands(t_list *list, t_hell *mini, t_env **lst);
int		choose_and_acquire(t_hell *mini, t_env **lst, t_list *list);
char	**convert_to_2d_array(t_env *env_list);
void	ctrl_c(int sig);
int		pipe_check(t_hell *mini);
void	ctrl_that_thing(int sig);

#endif