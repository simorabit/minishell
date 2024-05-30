#include "../minishell.h"

int get_numof_pipes(t_lexer *lexer)
{
    t_lexer *tmp;
    int counter;

    counter = 0;
    tmp = lexer;
    while (tmp)
    {
        if (tmp->token == mpipe)
            counter++;
        tmp = tmp->next;
    }
    return counter;
}