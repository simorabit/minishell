/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:45:40 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/26 18:27:19 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SYNTAX_ERROR			"syntax Error\n"
# define INPUT_ERROR			"Please Enter Valid Argument\n"
# define ERROR_IN_ALLOCATION	"Error In Allocation"
# define SINGLE_QUOTE			'\'' 
# define DOUBLE_QUOTE			'\"' 

typedef enum s_token
{
	word,
	mpipe,
	redirect_in	,
	redirect_out,
	heredoc,
	redirect_app,
	env_var
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
	t_wquotes		wquotes;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_simple_cmds
{
	char					**str;
	// int                     (*builtin)(t_tools *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

//lexer_list
t_lexer	*ft_lstlast(t_lexer *lexer);
t_lexer	*ft_lstnew(int content);
int		ft_lstsize(t_lexer *lst);
void	ft_lstadd_back(t_lexer **lexer, t_lexer *new);
void ft_lst_remove(t_lexer **lexer, int index);
//main
int		handel_quotes(char *line);

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

//utils_quotes_spaces
void	set_redir(char *s, int *j, int *i, char c);
int		is_redir_has_found(char c);
int		handel_quotes(char *line);
int		quotes(char *line, char q);

//syntax error
int		syntax_error(t_lexer **lexer);
// utils_split
int		is_withspaces(char c);
char	*ft_word(char *s, char **arr, char ind, char quotes);
void	wait_till_end(char **s);

//expanding
void	*handel_expanding(t_lexer **lexer);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		str_chr(char *s, char c);
char	*ft_strdup(const char *s1);
char	**or_split(char const *s, char c);
char *handel_expand_dq(char *s, int *pos);
char *allocate_for_expand(char *str, int *pos);
#endif
