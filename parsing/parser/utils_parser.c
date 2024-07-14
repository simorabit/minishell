#include "../../minishell.h"

void init_arrays(t_simple_cmds *cmds)
{
    if (cmds)
    {
        cmds->args = NULL;
        cmds->cmmd = NULL;
        cmds->in_file = -2;
        cmds->out_file = -2;
        cmds->heredoc = -2;
        cmds->aout_file = -2;
    }
}
int get_lcmd(t_lexer *lexer)
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
