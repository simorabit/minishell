/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:35:32 by souaouri          #+#    #+#             */
/*   Updated: 2024/05/17 00:35:32 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parsing/get_next_line/get_next_line.h"
# include <fcntl.h>

# define SYNTAX_ERROR			"syntax Error\n"
# define INPUT_ERROR			"Please Enter Valid Argument\n"
# define ERROR_IN_ALLOCATION	"Error In Allocation"
# define SINGLE_QUOTE			'\'' 
# define DOUBLE_QUOTE			'\"' 

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"


typedef enum s_token
{
	word,
	mpipe,
	redirect_in	,
	redirect_out,
	heredoc,
	redirect_app,
	delimiter,
	file
}	t_token;

typedef enum wquotes
{
	doubleQuotes,
	singleQuotes,
}	t_wquotes;

typedef struct s_lexer
{
	char			*str;
	t_token			token;
	int				i;
	int				expanded;
	t_wquotes		wquotes;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_simple_cmds
{
    char    *cmd;
    char    **args;
	char	**cmmd;
    int		in_file;
    int		out_file;
    int		aout_file;
    int		heredoc;	
	struct s_simple_cmds *next;
} t_simple_cmds; 

typedef struct env
{
	char		*content;
	struct env	*next;
}			t_env;

//libift func
char *ft_strncpy(char *s, int len);
int	ft_strncmp(const char *s1, const char *s2, unsigned int n);
void	ft_putstr_fd(char *str, int fd);

//lexer_list
t_lexer	*ft_lstlast(t_lexer *lexer);
t_lexer	*ft_lstnew(int content);
int		ft_lstsize(t_lexer *lst);
void	ft_lstadd_back(t_lexer **lexer, t_lexer *new);
void ft_lst_remove(t_lexer **lexer, int index);

//main
int		handel_quotes(char *line);

//remove quotes
void remove_quotes(t_lexer **lexer);

//quotes_spaces
void	*add_spaces(char *line);

//tokenizer
void	tokenizer(char **res, t_lexer **lexer);

//utils_string
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s);

//utils_free
void	free_list(char **list);
void	allocation_error(char *s);
void	error_msg(char *s);
void	free_lexer(t_lexer *lexer);

//utils_quotes_spaces
void	set_redir(char *s, int *j, int *i, char c);
int		is_redir_has_found(char c);
int		handel_quotes(char *line);
int		quotes(char *line, char q);

//syntax error
int		syntax_error(t_lexer **lexer);

// utils_split
char	*ft_word(char *s, char **arr, char ind, char quotes);
void	wait_till_end(char **s);
void count_if_char(char *s, int *i);

//parser
t_simple_cmds	*ft_lstnew_cmd(void);
int	ft_lstsize_cmd(t_simple_cmds *lst);
void	ft_lstadd_back_cmd(t_simple_cmds **cmds, t_simple_cmds *new);
t_simple_cmds	*ft_lstlast_cmd(t_simple_cmds *cmds);

int		get_lcmd(t_lexer *lexer);
int		open_files(t_lexer **lexer, t_token token);
int		save_heredoc(t_lexer **lexer);
void 	init_arrays(t_simple_cmds *cmds);
void 	*parser(t_lexer **lexer, t_simple_cmds **cmds, int len);
int 	handel_heredoc(char *del);

//expanding
void	handel_expanding(t_lexer **lexer);
char 	*expand_str(char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		str_chr(char *s, char c);
char	*ft_strdup(const char *s1);
char 	*handel_double_q(char *result, char *s, int *i, int *j);
char 	*handel_singleq(char *result, char *s, int *i, int *j);
char	*alloc_exp(char *str, int *pos);
int		get_len_ep(char *s);
int		end_of_proccessing(char c);
int		is_real_char(char c);
char 	*expand_str2(char *s);

//debugging
void	print_cmd(t_simple_cmds **cmds);
void 	printf_str(char *s);
void 	printf_int(int d);
void	print_lexer(t_lexer *lexer);

//execution
void	putstr(char *str, int i);
void	ft_fork(char *nood, t_env *list_env);
int		ft_strlen_1(char **ptr);
void	echo(char **cmd, t_simple_cmds *cmds);
void	classification_cmd(t_env *list_env, char **nood, t_simple_cmds *cmds);
void	ft_exec(char **cmd, char **env);
void	*free_double_ptr(char	**ptr);
void	child(char *nood, char **env);
void	parent(char *nood, char **env);
char	**ft_split_exe(char *s, char c);

//utils
int	no_quotes(char *line, int i);
int has_quotes(char *s);
int	is_quotes(char c);
int	is_withspaces(char c);
int	is_redirs(t_lexer *lexer);

// typedef struct list
// {
// 	t_container	content;
// 	struct list	*next;
// }			t_list;

// // virtual
char	*ft_strjoin(char *s1, char *s2);
void	ft_check(char *cmd, char **env);
char	*ft_strchr(char *s, int c);
char	*ft_find_path(char **env);
void	ft_find_pwd(void);
t_env	*get_env(char **env);
void	get_cd(char *cmd);
void	export_exe(char **cmd, t_env *list_env);
void	write_env(t_env *env);
char	**change_list_to_env(t_env *list_env);
int		ft_lstsize_env(t_env *lst);
void	multiple_cmd(t_env *env_list, t_simple_cmds *list);
t_env	*ft_lstnew_env(char *line);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	change_list(t_simple_cmds *list);
void	initialize_files(t_simple_cmds	*list);
char	**join_cmd_arg(char *cmd, char **arg);
#endif
// #endif