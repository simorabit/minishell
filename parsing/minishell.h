#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


#define SyntaxError "Syntax Error\n"
#define InputError "Please Enter Valid Argument\n"
#define ErrorInAllocation "Error In Allocation"
#define SingQuote '\'' 
#define DoubleQuote '\"' 

typedef enum s_token
{
    word,
    mpipe,
    redirect_in,
    redirect_out,
    heredoc,
    redirect_app,// >>
	doubleQuotes,
	singleQuotes,
	env_var 
}t_token;


typedef struct s_lexer
{
	char			*str;
	t_token			token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_simple_cmds
{
	char                    **str;
	// int                     (*builtin)(t_tools *, struct s_simple_cmds *);
	int                     num_redirections;
	char                    *hd_file_name;
	t_lexer                 *redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;


//lexer_list
t_lexer	*ft_lstlast(t_lexer *lexer);
t_lexer	*ft_lstnew(int content);
int		ft_lstsize(t_lexer *lst);
void	ft_lstadd_back(t_lexer **lexer, t_lexer *new);

//main
int		handel_quotes(char *line);

//quotes_spaces
void	*add_spaces(char *line);

//tokenizer
void tokenizer(char **res, t_lexer **lexer);

//utils_string
size_t	ft_strlen(const char *s);
int     ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s);

//utils_free
void	free_list(char **list);
void	allocation_error(char *s);
void	error_msg(char *s);

//utils_quotes_spaces
void set_redir(char *s, int *j, int *i, char c);
int is_redir_has_found(char c);
int handel_quotes(char *line);
int quotes(char *line, char q);

//syntax error
void syntax_error(t_lexer **lexer);

// utils_split
int is_withspaces(char c);
char *get_from_quotes(char *s, char **arr, char ind, char quotes);
char *ft_word(char *s, char **arr, int ind);
void wait_till_end(char const **s, int flag);