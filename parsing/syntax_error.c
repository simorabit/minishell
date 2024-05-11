#include "minishell.h"

int is_redirs(t_lexer *lexer)
{
    return (lexer->token >= 2 && lexer->token <= 5);
}
int syn_err_checker(t_lexer **lexer)
{
    t_lexer *tmp;

    tmp = *lexer;
    while (tmp)
    {
        if(is_redirs(tmp))
        {
            if(!tmp->next)
                return 0;
        }
        else if(tmp->token == mpipe)
        {
            if(!tmp->next || !tmp->prev)
                return 0;
        }
        tmp = tmp->next;
    }
    return 1;
}
void syntax_error(t_lexer **lexer)
{
    if(!syn_err_checker(lexer))
        error_msg(SyntaxError);
}