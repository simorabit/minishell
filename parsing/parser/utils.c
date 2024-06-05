#include "../minishell.h"

void init_arrays(t_simple_cmds *cmds)
{
    if (cmds)
    {
        cmds->args = NULL;
        cmds->in_file = NULL;
        cmds->out_file = NULL;
        // cmds->heredoc = NULL;
        cmds->aout_file = NULL;
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