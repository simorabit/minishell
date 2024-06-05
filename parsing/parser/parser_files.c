#include "../minishell.h"

void *save_app_files(t_lexer **lexer, t_simple_cmds *cmds)
{
    t_lexer *tmp;
    int len;
    int i;

    i = 0;
    len = 0;
    tmp = (*lexer)->next;
    while (tmp && (tmp->token == word || tmp->token == redirect_app))
    {
        if (tmp->token == word)
            len++;
        tmp = tmp->next;
    }
    cmds->aout_file = malloc((len + 1) * sizeof(char *));
    if (!cmds->aout_file)
        return NULL;
    (*lexer) = (*lexer)->next;
    while (i < len)
    {
        if ((*lexer)->token == word)
            cmds->aout_file[i++] = ft_strdup((*lexer)->str);
        (*lexer) = (*lexer)->next;
    }
    cmds->aout_file[i] = NULL;
    return cmds;
}
void *save_heredoc(t_lexer **lexer, t_simple_cmds *cmds)
{
    t_lexer *tmp;
    int     len;
    char    *del;

    len = 0;
    tmp = (*lexer)->next;
    while (tmp && (tmp->token == word || tmp->token == heredoc))
    {
        if (tmp->token == word && (tmp->next == NULL || 
                tmp->next->token == mpipe))
            del = ft_strdup(tmp->str);
        tmp = tmp->next;
    }
    // need to complite tomorrow
    return cmds;
}
void *save_out_files(t_lexer **lexer, t_simple_cmds *cmds)
{
    t_lexer *tmp;
    int len;
    int i;

    i = 0;
    len = 0;
    tmp = (*lexer)->next;
    while (tmp && (tmp->token == word || tmp->token == redirect_out))
    {
        if (tmp->token == word)
            len++;
        tmp = tmp->next;
    }
    cmds->out_file = malloc((len + 1) * sizeof(char *));
    if (!cmds->out_file)
        return NULL;
    (*lexer) = (*lexer)->next;
    while (i < len)
    {
        if((*lexer)->token == word)
            cmds->out_file[i++] = ft_strdup((*lexer)->str);
        (*lexer) = (*lexer)->next;
    }
    cmds->out_file[i] = NULL;
    return cmds;
}
void *save_in_files(t_lexer **lexer, t_simple_cmds *cmds)
{
    t_lexer *tmp;
    int len;
    int i;

    i = 0;
    len = 0;
    tmp = (*lexer)->next;
    while (tmp && (tmp->token == word || tmp->token == redirect_in))
    {
        if (tmp->token == word)
            len++;
        tmp = tmp->next;
    }
    cmds->in_file = malloc((len + 1) * sizeof(char *));
    if (!cmds->in_file)
        return NULL;
    (*lexer) = (*lexer)->next;
    while (i < len)
    {
        if((*lexer)->token == word)
            cmds->in_file[i++] = ft_strdup((*lexer)->str);
        (*lexer) = (*lexer)->next;
    }
    cmds->in_file[i] = NULL;
    return cmds;
}
